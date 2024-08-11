from flask import Flask, render_template, request, redirect, url_for
import os
import yaml

app = Flask(__name__)
CONFIG_DIR = '../../modules/vins_core/configurations'

@app.route('/')
def index():
    files = os.listdir(CONFIG_DIR)
    return render_template('index.html', files=files)

@app.route('/edit/<filename>', methods=['GET', 'POST'])
def edit_file(filename):
    file_path = os.path.join(CONFIG_DIR, filename)
    if request.method == 'POST':
        content = request.form['content']
        with open(file_path, 'w') as file:
            yaml.safe_dump(yaml.safe_load(content), file)
        return redirect(url_for('index'))
    else:
        with open(file_path, 'r') as file:
            content = file.read()
        return render_template('edit.html', filename=filename, content=content)

if __name__ == '__main__':
    app.run(debug=True)