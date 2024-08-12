import cv2
import os
import argparse


parser = argparse.ArgumentParser(description="Combine frames from given dataset's sequence to video file")

parser.add_argument("--path", type=str, help="Path to sequence directory")
parser.add_argument("--filename", type=str, help="Output video filename")
parser.add_argument("--fps", type=int, help="Output video FPS")

args = parser.parse_args()

dataset_directory = args.path
filename = args.filename
fps = args.fps

if dataset_directory is None:
    dataset_directory = "/home/apin/video_dataset/KITTI/sequences/00/image_0/"

if filename is None:
    filename = "video.mp4"

if fps is None:
    fps = 10

img_list = sorted(
    [img for img in os.listdir(dataset_directory) if os.path.isfile(os.path.join(dataset_directory, img))]
)

# print(img_list)

img = cv2.imread(dataset_directory + img_list[0])

height, width, _ = img.shape

fourcc = cv2.VideoWriter_fourcc(*"mp4v")
video = cv2.VideoWriter(filename, fourcc, fps, (width, height))

for img_path in img_list:
    img = cv2.imread(dataset_directory + img_path)

    cv2.imshow("fuck", img)

    video.write(img)
    
    key = cv2.waitKey(int(1 / fps * 1e3))

    if key == 27:
        break

video.release()