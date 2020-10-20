const UVCControl = require('uvc-control')
const usb = require('usb');
const sleep = (waitTimeInMs) => new Promise(resolve => setTimeout(resolve, waitTimeInMs));

const vid = 0x046d;
const pid = 0x082d;

const webcams = usb.getDeviceList().filter(device => {
          return device.deviceDescriptor.idVendor === vid &&
          device.deviceDescriptor.idProduct === pid
});

//console.log("Matching Webcams");
//console.log(webcams);

webcams.forEach( webcam => {
    const camera = new UVCControl({vid: webcam.deviceDescriptor.idVendor, 
        pid: webcam.deviceDescriptor.idProduct, 
        deviceAddress: webcam.deviceAddress})
    camera.set('auto_focus', 0).then(() => {
        console.log('AutoFocus turned off!')
        camera.set('absolute_focus', 100).then(() => {
            console.log('Auto Focus set to 100 for 2 seconds');
            sleep(2000).then(() => {
                camera.set('absolute_focus', 0).then(() => {
                    console.log('Auto Focus set to 0');
                })
            });   
        })
    })
})
