# -------------------------------------------------------------
# led25GpioTurnOn.sh
# Key-point: we can manage a device connected on a GPIO pin by
# using the GPIO shell library. 
# The pin 25 is physical 22 and Wpi 6.
#	sudo bash led25GpioTurnOn.sh
# -------------------------------------------------------------
#!/bin/bash
#i=0
#tempo=50
#limit=$1
#num=$((limit/tempo))

echo $$ > PidOfBlinkingLed.txt


while : #[ $i -le $num ]
do
	gpio mode 6 out #
	gpio write 6 1 #
	sleep 0.05
	gpio mode 6 out
	gpio write 6 0
	#i=$((i+1))
done

