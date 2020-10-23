const UVCControl = require("uvc-control");
const usb = require("usb");

// Filter Webcams by VID and PID (These are for the C920)
const vid = 0x046d;
const pid = 0x082d;

// Find all devices that match the above VID and PID
const filteredUSBDevices = usb.getDeviceList().filter((device) => {
  return (
    device.deviceDescriptor.idVendor === vid &&
    device.deviceDescriptor.idProduct === pid
  );
});

//console.log(filteredUSBDevices);

// open a control device for each.
const webcams = filteredUSBDevices.map((filteredDevice) => {
  return new UVCControl({
    vid: filteredDevice.deviceDescriptor.idVendor,
    pid: filteredDevice.deviceDescriptor.idProduct,
    deviceAddress: filteredDevice.deviceAddress,
  });
});

const setAutoFocus = (cameraIndex, focusSetting) => {
  if (cameraIndex < webcams.length) {
    return webcams[cameraIndex]
      .set("auto_focus", focusSetting)
      .then(() => console.log("Auto Focus set to " + focusSetting));
  } else {
    return Promise.reject(new Error("out of bounds index"));
  }
};

const adjustFocus = (cameraIndex, focusChangeAmount) => {
  if (cameraIndex < webcams.length) {
    return webcams[cameraIndex].get("absolute_focus").then((value) => {
      const currentFocusValue = parseInt(value.wFocusAbsolute);
      console.log("Current Focus setting:", currentFocusValue);
      const newFocusValue = currentFocusValue + focusChangeAmount;
      console.log("New Focus Value:", newFocusValue);
      return setFocus(cameraIndex, newFocusValue);
    });
  } else {
    return Promise.reject(new Error("out of bounds index"));
  }
};

const setFocus = (cameraIndex, newFocusValue) => {
  if (cameraIndex < webcams.length) {
    console.log("New Focus Value:", newFocusValue);
    if (newFocusValue < 250 && newFocusValue >= 0) {
      return webcams[cameraIndex]
        .set("absolute_focus", newFocusValue)
        .then(() => {
          console.log("Set Focus to to " + newFocusValue);
        });
    } else {
      return Promise.reject(new Error("Value out of range"));
    }
  } else {
    return Promise.reject(new Error("out of bounds index"));
  }
};

exports.setAutoFocus = setAutoFocus;
exports.adjustFocus = adjustFocus;
exports.setFocus = setFocus;
exports.webcams = webcams;
