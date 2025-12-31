import time
import cv2
import numpy as np
import mediapipe as mp
import serial
from serial.tools import list_ports

# =========================
# CONFIG
# =========================
EAR_THRESHOLD = 0.23
FRAMES_DROWSY = 20      # how many frames in a row = drowsy
FRAMES_AWAKE = 15       # how many frames in a row = awake to turn relay OFF

MODEL_PATH = "face_landmarker.task"

# =========================
# SERIAL + RELAY
# =========================
def open_arduino_serial(baud=9600):
    ports = list_ports.comports()
    for p in ports:
        desc = p.description.lower()
        if "usb" in desc or "arduino" in desc or "wchusb" in desc or "slab" in desc:
            try:
                print(f"[INFO] Trying port {p.device} ({p.description})")
                ser = serial.Serial(p.device, baud, timeout=1)
                time.sleep(2)
                print(f"[INFO] Connected to {p.device}")
                return ser
            except Exception as e:
                print(f"[WARN] Failed to open {p.device}: {e}")
    print("[WARN] No Arduino-like serial port found.")
    return None

ser = open_arduino_serial(9600)

def send_relay(on: bool):
    """
    on=True  -> send '0'  (RELAY ON)
    on=False -> send '1'  (RELAY OFF)
    """
    global ser
    if ser is None:
        print("[DEBUG] send_relay called but serial is None")
        return

    try:
        if on:
            ser.write(b'1')
            print("[SERIAL] Sent '1' -> RELAY ON")
        else:
            ser.write(b'0')
            print("[SERIAL] Sent '0' -> RELAY OFF")
    except Exception as e:
        print("[ERROR] Serial write failed:", e)
        ser = None


# =========================
# MEDIAPIPE SETUP
# =========================
BaseOptions = mp.tasks.BaseOptions
FaceLandmarker = mp.tasks.vision.FaceLandmarker
FaceLandmarkerOptions = mp.tasks.vision.FaceLandmarkerOptions
VisionRunningMode = mp.tasks.vision.RunningMode

LEFT_EYE_IDX = [33, 133, 159, 145]
RIGHT_EYE_IDX = [362, 263, 386, 374]

def euclidean_dist(a, b):
    return np.linalg.norm(a - b)

def eye_aspect_ratio(landmarks, image_w, image_h, eye_idx):
    outer = np.array([landmarks[eye_idx[0]].x * image_w,
                      landmarks[eye_idx[0]].y * image_h])
    inner = np.array([landmarks[eye_idx[1]].x * image_w,
                      landmarks[eye_idx[1]].y * image_h])
    upper = np.array([landmarks[eye_idx[2]].x * image_w,
                      landmarks[eye_idx[2]].y * image_h])
    lower = np.array([landmarks[eye_idx[3]].x * image_w,
                      landmarks[eye_idx[3]].y * image_h])

    horiz = euclidean_dist(outer, inner)
    vert = euclidean_dist(upper, lower)

    if horiz == 0:
        return 0.0
    return vert / horiz


def main():
    options = FaceLandmarkerOptions(
        base_options=BaseOptions(model_asset_path=MODEL_PATH),
        running_mode=VisionRunningMode.VIDEO,
        num_faces=1,
        min_face_detection_confidence=0.5,
        min_face_presence_confidence=0.5,
        min_tracking_confidence=0.5,
    )

    cap = cv2.VideoCapture(0)
    if not cap.isOpened():
        print("[ERROR] Could not open webcam.")
        return

    drowsy_frames = 0
    awake_frames = 0
    relay_on = False

    start_time = time.time()

    with FaceLandmarker.create_from_options(options) as landmarker:
        while True:
            ret, frame = cap.read()
            if not ret:
                print("[WARN] Failed to grab frame")
                break

            h, w, _ = frame.shape
            rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=rgb)

            timestamp_ms = int((time.time() - start_time) * 1000)
            result = landmarker.detect_for_video(mp_image, timestamp_ms)

            if result.face_landmarks:
                face_landmarks = result.face_landmarks[0]

                left_ear = eye_aspect_ratio(face_landmarks, w, h, LEFT_EYE_IDX)
                right_ear = eye_aspect_ratio(face_landmarks, w, h, RIGHT_EYE_IDX)
                ear = (left_ear + right_ear) / 2.0

                cv2.putText(frame, f"EAR: {ear:.3f}", (30, 30),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)

                if ear < EAR_THRESHOLD:
                    drowsy_frames += 1
                    awake_frames = 0
                else:
                    awake_frames += 1
                    drowsy_frames = 0

                # ---- trigger relay ON if drowsy for long enough ----
                if drowsy_frames >= FRAMES_DROWSY and not relay_on:
                    cv2.putText(frame, "DROWSY! RELAY ON", (30, 70),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
                    send_relay(True)   # -> '0'
                    relay_on = True

                # ---- trigger relay OFF if awake for long enough ----
                if awake_frames >= FRAMES_AWAKE and relay_on:
                    cv2.putText(frame, "Awake (Reset Relay)", (30, 70),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 2)
                    send_relay(False)  # -> '1'
                    relay_on = False

            else:
                cv2.putText(frame, "No face detected", (30, 30),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 255), 2)

            cv2.imshow("Drowsiness + Relay", frame)

            key = cv2.waitKey(1) & 0xFF
            if key == ord('q'):
                break
            elif key == ord('0'):
                # manual ON
                send_relay(True)
                relay_on = True
            elif key == ord('1'):
                # manual OFF
                send_relay(False)
                relay_on = False
                drowsy_frames = 0
                awake_frames = 0

    cap.release()
    cv2.destroyAllWindows()
    if ser:
        ser.close()


if __name__ == "__main__":
    main()
