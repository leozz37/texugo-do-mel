#!/bin/sh

cd /root
./core-messaging config/ServerConfiguration.json

exec "$@"