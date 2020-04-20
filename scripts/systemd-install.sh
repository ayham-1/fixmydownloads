#!/bin/sh

cp services/fixmydownloads.service /etc/systemd/system/fixmydownloads.service
systemctl enable fixmydownloads.service
