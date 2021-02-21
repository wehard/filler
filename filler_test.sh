#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

PLAYER=$1

MAPS_FOLDER="./resources/maps/"
MAPS=$3

OPP_FOLDER="./resources/players/linux/"
OPPS=$2

if [ $# -ne 3 ]; then
	echo "./filler_test [player] [opp/*.filler] [map/*]"
	exit 1
fi

for opp in $OPP_FOLDER$OPPS
do
	for map in $MAPS_FOLDER$MAPS
	do
		let "count = 0"
		for n in `seq 1 5`
		do
			./resources/filler_vm_old -q -p1 $PLAYER -p2 "$opp" -f "$map" > quiet
			line=`grep won filler.trace`
			echo "$line"
			if [ "$line" = "$PLAYER won" ];
			then let "count = $count + 1"
			fi
		done
		let "win = 0"
		let "win = ($count * 100) / 5"
		if [ $win -ge 50 ];
		then echo -e "${GREEN} $win % of win against $opp on map $map ${NC}"
		else 
			echo -e "${RED} $win % of win against $opp on map $map ${NC}"
		fi
	done
done
