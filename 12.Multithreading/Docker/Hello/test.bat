docker --version
docker build -t my-hello-app .
docker run --rm my-hello-app
docker run --rm my-hello-app /bin/bash -c "echo GCC: && g++ --version | head -1 && echo Vim: && vim --version | head -1"
pause