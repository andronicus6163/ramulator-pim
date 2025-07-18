# Use an older Ubuntu version for pin2.4

FROM ubuntu:18.04

RUN apt-get update && \
	apt-get -y install build-essential && \
	apt-get -y install scons && \
	apt-get -y install automake && \
	apt-get -y install autoconf && \
	apt-get -y install m4 && \
	apt-get -y install perl && \
	apt-get -y install flex && \
	apt-get -y install bison && \
	apt-get -y install byacc && \
	#apt-get -y install libconfig-dev && \
	#apt-get -y install libconfig++-dev && \
	apt-get -y install libhdf5-dev && \
	apt-get -y install libelf-dev && \
	apt-get -y install vim && \
	apt-get -y install libboost-all-dev && \
	apt-get -y install libxerces-c-dev

# Create working directory
WORKDIR /workspace

# Copy local files into the container
COPY ramulator/ /workspace/ramulator/
COPY zsim-ramulator/ /workspace/zsim-ramulator/
COPY common/ /workspace/common/
COPY compileramulator.sh /workspace/
COPY README.md /workspace/

WORKDIR /workspace/zsim-ramulator
RUN sh compile.sh

WORKDIR /workspace/common/DRAMPower
RUN make -j4

WORKDIR /workspace/ramulator
RUN make -j4

CMD ["bash"]
