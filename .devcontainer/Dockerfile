FROM zephyrprojectrtos/zephyr-build:v0.26-branch

USER root

ARG ZEPHYR_SDK_VERSION
ARG ALIF_SE_TOOLS
ARG PIP_INSTALL="pip3 install"

# Remove old cmake version from apt and replace it with the lastest using pipinstall
RUN apt-get purge -y  \
  cmake 

RUN apt-get update && apt-get install -y \
  curl \
  udev \
  libncurses5 \
  libxcb-render-util0-dev \
  libxrender1\
  libxcb-shape0 \
  libxcb-randr0 \
  libxcb-xfixes0 \
  libxcb-sync1 \
  libxcb-shm0 \
  libxcb-icccm4 \
  libxcb-keysyms1 \
  libxcb-image0 \
  libxkbcommon0 \
  libxkbcommon-x11-0 \
  libfontconfig1 \
  libfreetype6 \
  libxext6 \
  libx11-xcb1 \
  && rm -rf /var/lib/apt/lists/* 

RUN $PIP_INSTALL pyelftools
RUN $PIP_INSTALL cmake


# Install Zephyr SDK
RUN wget -q "https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v${ZEPHYR_SDK_VERSION}/zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz" \
  && tar xvf zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz \
  && mv zephyr-sdk-${ZEPHYR_SDK_VERSION} /opt/ \
  && rm zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz \
  && cd /opt/zephyr-sdk-${ZEPHYR_SDK_VERSION} \
  && ./setup.sh -h -c -t arm-zephyr-eabi

# Get the app-release-exec-linux se-tools from Alif
RUN mkdir -p ${ALIF_SE_TOOLS} 
RUN wget -q https://alifsemi.com/download/APFW0002 -O app-release-exec-linux.tar \
  && tar xf app-release-exec-linux.tar \
  && mv app-release-exec-linux/* ${ALIF_SE_TOOLS} \
  && rm app-release-exec-linux.tar

# Set ttyACM0 as the default serial port for the Alif SE tools
RUN printf "comport /dev/ttyACM0\ntimeout tx 2\ntimeout rx 0\nstopbits 1\nbytesize 8\nrtscts 0\nxonxoff 0\n" > ${ALIF_SE_TOOLS}/isp_config_data.cfg

# Install JLink
RUN wget --post-data="accept_license_agreement=accepted&submit=Download+software" "https://www.segger.com/downloads/jlink/JLink_Linux_V828_x86_64.deb" \
  && dpkg --unpack JLink_Linux_V828_x86_64.deb \
  && rm /var/lib/dpkg/info/jlink.postinst -f \
  && dpkg --configure jlink \
  && apt install -yf \
  && rm JLink_Linux_V828_x86_64.deb
