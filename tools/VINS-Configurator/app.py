from flask import Flask, render_template, request, redirect, url_for
import os
from ruamel.yaml import YAML
from ruamel.yaml.comments import CommentedMap
import sys
from subprocess import Popen, PIPE


from process_configs import *


app = Flask(__name__)
CONFIG_DIR = './configs'

yaml = YAML()
yaml.preserve_quotes = True  # Сохраняет кавычки вокруг строк

@app.route('/')
def index():
    files = os.listdir(CONFIG_DIR)
    return render_template('index.html', files=files)


@app.route('/edit/<filename>', methods=['GET', 'POST'])
def edit_file(filename):
    file_path = os.path.join(CONFIG_DIR, filename)

    if request.method == 'POST':
        return save_file(filename)
    else:
        return get_file(filename)


def save_file(filename):
    file_path = os.path.join(CONFIG_DIR, filename)

    content = request.form.to_dict()
    
    current_content = {key: content[key] for key in content}

    print(current_content)


    with open(file_path, 'r') as file:
        yaml_content = yaml.load(file)
        app.logger.info(yaml_content)

    yaml_content['current'] = current_content
    with open(file_path, 'w') as file:
        yaml.dump(yaml_content, file)

    return redirect(url_for('index'))



def get_file(filename):
    file_path = os.path.join(CONFIG_DIR, filename)

    match (filename[:-5]):
        case "config":
            return process_config(file_path)

        case "dataset_config":
            return process_dataset(file_path)

        case "video_config":
            return process_video(file_path)
        
        case "camera_config":
            return process_camera(file_path)

def process_config(file_path):
    filename = file_path.split('/')[-1][:-5]
    print(filename)

    with open(file_path, 'r') as file:
        content = yaml.load(file)
    
    display_content = {
        "source": ["dataset", "video", "camera"]
    }

    current_content = {key: value for key, value in content.items() if key == 'current'}

    return render_template('edit.html', filename=filename, content=display_content, default=current_content)


def process_dataset(file_path):
    filename = file_path.split('/')[-1][:-5]
    print(filename)

    with open(file_path, 'r') as file:
        content = yaml.load(file)

    current_content = {key: value for key, value in content.items() if key == 'current'}

    datasets = os.listdir("../../datasets")
    datasets.pop(datasets.index("custom"))

    current_dataset = current_content["current"]["dataset"]

    sequences = sorted(os.listdir(f"../../datasets/{current_dataset}/sequences"))

    display_content = {
        "dataset": datasets,
        "sequence": sequences
    }

    return render_template('edit.html', filename=filename, content=display_content, default=current_content)


def process_video(file_path):
    filename = file_path.split('/')[-1][:-5]
    print(filename)

    with open(file_path, 'r') as file:
        content = yaml.load(file)

    current_content = {key: value for key, value in content.items() if key == 'current'}

    video_folder = "../../" + current_content["current"]["path"] + "/sequences"

    display_content = {
        "path": [current_content["current"]["path"]],
        "video": os.listdir(video_folder),
        "fps": [10, 30, 60, 120]
    }

    print(display_content)

    return render_template('edit.html', filename=filename, content=display_content, default=current_content)


def process_camera(file_path):
    filename = file_path.split('/')[-1][:-5]
    print(filename)

    with open(file_path, 'r') as file:
        content = yaml.load(file)

    current_content = {key: value for key, value in content.items() if key == 'current'}

    video_devices = [int(video_device[5:]) for video_device in os.listdir("/dev") if "video" in video_device]

    display_content = {
        "device": video_devices,
        "fps": [10, 30, 60, 120]
    }

    return render_template('edit.html', filename=filename, content=display_content, default=current_content)


if __name__ == '__main__':
    app.run(debug=True)