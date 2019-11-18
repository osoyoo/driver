#!/bin/bash

# download files
echo '########################## download files ################'
apt-get update
apt-get  install  rpi.gpio  -y
mkdir   /home/pi/osoyoo-robot
mkdir   /home/pi/osoyoo-robot/cam-robot

cd /home/pi/osoyoo-robot/cam-robot && 
wget  http://osoyoo.com/driver/WebIOPi-0.7.1.tar.gz &&
wget  http://osoyoo.com/driver/mjpg-streamer.tar.gz &&
wget  http://osoyoo.com/driver/robot.tar.gz &&
tar  -xzvf  WebIOPi-0.7.1.tar.gz &&
tar  -xzvf   mjpg-streamer.tar.gz &&
tar  -xzvf  robot.tar.gz

cd /home/pi/osoyoo-robot/cam-robot/WebIOPi-0.7.1 && 
wget   http://osoyoo.com/driver/webiopi-pi2bplus.patch &&
patch    -p1   -i  webiopi-pi2bplus.patch

echo '########################## download complete ################'
echo '########################## install webiopi ################'
cd /home/pi/osoyoo-robot/cam-robot/WebIOPi-0.7.1 &&
sed -i 's/read response//g' setup.sh &&
./setup.sh

echo '########################## install webiopi end ################'

if ! grep -q "bcm2835-v4l2" /etc/modules
then
	sed -i -e "\$abcm2835-v4l2" /etc/modules
fi
if ! grep -q "i2c-bcm2708" /etc/modules
then
	sed -i -e "\$ai2c-bcm2708" /etc/modules
fi

echo '########################## install mjpeg stramer ################'
apt-get install libv4l-dev libjpeg8-dev -y
apt-get install subversion -y

sed -i 's/V4L2_PIX_FMT_MJPEG/V4L2_PIX_FMT_YUYV/g' /home/pi/osoyoo-robot/cam-robot/mjpg-streamer/plugins/input_uvc/input_uvc.c
cd  /home/pi/osoyoo-robot/cam-robot/mjpg-streamer && make all

echo '########################## install mjpeg stramer end ################'

echo '########################## setting parameter ################'
if ! grep -q "myscript = /home/pi/osoyoo-robot/cam-robot/robot/script.py" /etc/webiopi/config
then
	sed -i '/#myscript = \/home\/pi\/webiopi\/examples\/scripts\/macros\/script.py/a myscript = \/home\/pi\/osoyoo-robot\/cam-robot\/robot\/script.py' /etc/webiopi/config
fi
if ! grep -q "doc-root = /home/pi/osoyoo-robot/cam-robot/robot" /etc/webiopi/config
then
	sed -i '/#doc-root = \/home\/pi\/webiopi\/examples\/scripts\/macros/a doc-root = \/home\/pi\/osoyoo-robot\/cam\-robot\/robot' /etc/webiopi/config
fi
if ! grep -q "pwm0 = PCA9685 slave:0x40" /etc/webiopi/config
then
	sed -i '/MCP23017 slave:0x22/a pwm0 = PCA9685 slave:0x40' /etc/webiopi/config
fi
$1 = 0
echo '########################## enable camera ################'
grep "start_x=1" /boot/config.txt
if grep "start_x=1" /boot/config.txt
then
	$1 = 1
        sed -i "s/start_x=0/start_x=1/g" /boot/config.txt
fi
echo '########################## enable i2c ################'
if grep -q "^dtparam=i2c_arm=on" /boot/config.txt
then
	echo "Already enabled i2c"
else
	$1 = 1
	sed -i -e "\$adtparam=i2c_arm=on" /boot/config.txt
	sed -i -e "\$adtparam=i2c1=on" /boot/config.txt
fi

echo '########################## enable autostart ################'

echo -e "#!/bin/bash\n(cd /home/pi/osoyoo-robot/cam-robot/mjpg-streamer && sudo ./start.sh) & sudo webiopi -d -c /etc/webiopi/config\n" > /etc/init.d/superscript
echo -e "#!/bin/bash\n(cd /home/pi/osoyoo-robot/cam-robot/mjpg-streamer && sudo ./start.sh) & sudo webiopi -d -c /etc/webiopi/config\n" > /home/pi/superscript
sudo chmod 777 /etc/init.d/superscript
sudo chmod 777 /home/pi/superscript
sudo update-rc.d superscript defaults

if grep -q "^@./superscript" /home/pi/.config/lxsession/LXDE-pi/autostart
then
	echo "Autostart already configured."
else
	sed -i -e "\$a@midori" /home/pi/.config/lxsession/LXDE-pi/autostart
	sed -i -e "\$a@./superscript" /home/pi/.config/lxsession/LXDE-pi/autostart
fi
reboot