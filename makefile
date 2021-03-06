BINARY_READOUT=smartpireadout
BINARY_SERVER=smartpiserver
BINARY_FTPUPLOAD=smartpiftpupload

VERSION=0.3.7
BUILD_TIME=`date +%FT%T%z`

BUILDPATH=$(CURDIR)
GO=$(shell which go)
GOBUILD=$(GO) build
GOINSTALL=$(GO) install
GOCLEAN=$(GO) clean
GOGET=$(GO) get

export GOPATH=$(CURDIR)

all: makedir get buildsmartpireadout buildsmartpiserver buildsmartpiftpupload
#all: makedir get buildsmartpireadout 

makedir:
	@echo "start building tree..."
	@if [ ! -d $(BUILDPATH)/bin ] ; then mkdir -p $(BUILDPATH)/bin ; fi
	@if [ ! -d $(BUILDPATH)/pkg ] ; then mkdir -p $(BUILDPATH)/pkg ; fi

get:

buildsmartpireadout:
	@echo "start building smartpireadout..."
	GOPATH=$(BUILDPATH) $(GOBUILD) -o bin/$(BINARY_READOUT) src/main/readout.go
	@echo "building smartpireadout done"

buildsmartpiserver:
	@echo "start building smartpiserver..."
	GOPATH=$(BUILDPATH) $(GOBUILD) -o bin/$(BINARY_SERVER) src/main/server.go
	@echo "building smartpiserver done"

buildsmartpiftpupload:
	@echo "start building smartpiftpupload..."
	GOPATH=$(BUILDPATH) $(GOBUILD) -o bin/$(BINARY_FTPUPLOAD) src/main/ftpupload.go
	@echo "building smartpiftpupload done"

install:
	@echo install

#	if [ `pidof smartpireadout` > "0" ]
#		then killall smartpireadout
#	fi
#
#	if [ `pidof smartpiserver` > "0" ]
#		then killall smartpiserver
#	fi
#
#	if [ `pidof smartpiftpupload` > "0" ]
#		then killall smartpiftpupload
#	fi
#
#	if [ ! -d /var/tmp/smartpi ];
#		then mkdir -p /var/tmp/smartpi
#	fi
#
#	cat /etc/fstab | grep smartpi | grep -v "#"
#	if [ $? = 0 ];
#		then
#			:
#		else
#		echo "tmpfs /var/tmp/smartpi tmpfs nodev,nosuid,size=100M 0 0" >> /etc/fstab
#	fi
#
#
#	cat /etc/modules | grep i2c-bcm2708 | grep -v "#"
#	if [ $? = 0 ];
#		then
#			:
#		else
#		echo "i2c-bcm2708" >> /etc/modules
#	fi
#
#	cat /etc/modules | grep i2c-dev | grep -v "#"
#	if [ $? = 0 ];
#		then
#			:
#		else
#		echo "i2c-dev" >> /etc/modules
#	fi
#
#	cat /boot/config.txt | grep dtparam=i2c1=on | grep -v "#"
#	if [ $? = 0 ];
#		then
#			:
#		else
#			echo "dtparam=i2c1=on" >> /boot/config.txt
#	fi
#
#	cat /boot/config.txt | grep dtparam=i2c_arm=on | grep -v "#"
#	if [ $? = 0 ];
#		then
#			:
#		else
#			echo "dtparam=i2c_arm=on" >> /boot/config.txt
#	fi
#
#	if [ ! -d /var/smartpi/db ];
#		then mkdir -p /var/smartpi/db
#	fi
#
#	if [ ! -d /var/smartpi/www ];
#		then mkdir -p /var/smartpi/www
#	fi
#
#	cp $(BUILDPATH)/bin/* /usr/local/bin
#	cp $(BUILDPATH)/config/smartpi.conf /etc/smartpi
#	cp -r $(BUILDPATH)/public_html/* /var/smartpi/www
