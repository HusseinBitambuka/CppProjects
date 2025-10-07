#!/usr/bin/env bash
set -e
echo "Creating new BJFS disk image..."
dd if=/dev/zero of=disk/disk.img bs=512 count=128
