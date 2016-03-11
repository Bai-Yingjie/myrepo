#!/usr/bin/python

import subprocess
import re
import time
from datetime import datetime

dev = 'wlan0'
gwre = re.compile(r'^default via ([0-9\.]+) dev {}.*'.format(dev))

def log(msg):
    print '{}: {}'.format(str(datetime.now()), msg)

def find_gateway():
    cmd = ['ip', 'route', 'show']
    out = subprocess.check_output(cmd)

    g = gwre.findall(out)
    if g:
        return g[0]
    else:
        return None

def ping(ip):
    cmd = [ 'ping',
            '-c', '4',
            '-W', '5',
            ip ]
    
    try:
        out = subprocess.check_output(cmd)
        return True
    except subprocess.CalledProcessError, e:
        return False

def rfkill(on):
    op = 'block' if on else 'unblock'

    cmd = [ 'rfkill', op, 'wifi' ]
    subprocess.check_call(cmd)

def bounce():
    log('Bouncing {}'.format(dev))

    rfkill(True)
    time.sleep(1)
    rfkill(False)

oldgw = None
while True:
    gw = find_gateway()
    if gw:
        ok = ping(gw)
        if not ok:
            bounce()

    if gw != oldgw:
        log('New gateway: {}'.format(gw))
    oldgw = gw

    time.sleep(3)
