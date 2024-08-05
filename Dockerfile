FROM opencvcourses/opencv-docker

RUN apt-get update

WORKDIR /workspace

COPY . /workspace

CMD bash