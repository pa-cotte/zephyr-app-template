FROM zephyrprojectrtos/zephyr-build:v0.26-branch

USER root

ARG ZEPHYR_SDK_VERSION

# Install Zephyr SDK
RUN wget -q "https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v${ZEPHYR_SDK_VERSION}/zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz" \
  && tar xvf zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz \
  && mv zephyr-sdk-${ZEPHYR_SDK_VERSION} /opt/ \
  && rm zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz \
  && cd /opt/zephyr-sdk-${ZEPHYR_SDK_VERSION} \
  && ./setup.sh -h -c -t arm-zephyr-eabi