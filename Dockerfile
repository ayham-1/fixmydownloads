FROM opensuse/tumbleweed

#RUN zypper -n install cmake make gcc gcc-c++ git dpkg binutils devscripts
RUN zypper -n update
RUN zypper -n install cmake 
RUN zypper -n install make 
RUN zypper -n install gcc 
RUN zypper -n install gcc-c++
RUN zypper -n install dpkg
RUN zypper -n install rpm-build

COPY . fixmydownloads

WORKDIR fixmydownloads

ENTRYPOINT [ "/fixmydownloads/docker-entrypoint.sh" ]
