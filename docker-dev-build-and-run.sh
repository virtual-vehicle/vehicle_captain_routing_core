PORT="2222"

docker build -t clion/remote-cpp_routing-env:0.1 -f Dockerfiles/Dockerfile.remote-cpp-env .
docker run -d --cap-add sys_ptrace -p127.0.0.1:$PORT:22 --name v2x_routing-dev clion/remote-cpp_routing-env:0.1
ssh-keygen -f "$HOME/.ssh/known_hosts" -R "[localhost]:$PORT"
