

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import io
from PIL import Image
import csv

def to_rdm(deg_value):
    sign = deg_value/np.abs(deg_value)
    deg_value=np.abs(deg_value)
    ans = []
    ans.append((deg_value//30)*sign)
    deg_value = (deg_value%30)
    ans.append(np.floor(deg_value))
    deg_value = (deg_value - np.floor(deg_value))*60
    ans.append(np.floor(deg_value))
    deg_value = (deg_value - np.floor(deg_value))*60
    ans.append(np.floor(deg_value))
    deg_value = (deg_value - np.floor(deg_value))*60
    ans.append(np.floor(deg_value))
    deg_value = (deg_value - np.floor(deg_value))*60
    ans.append(np.floor(deg_value))
    return ans

def to_dms(deg_value):
    sign = deg_value/np.abs(deg_value)
    deg_value=np.abs(deg_value)
    ans = []
    ans.append((deg_value//1)*sign)
    deg_value = (deg_value - np.floor(deg_value))*60
    ans.append(np.floor(deg_value))
    deg_value = (deg_value - np.floor(deg_value))*60
    ans.append(np.floor(deg_value))
    deg_value = (deg_value - np.floor(deg_value))*60
    ans.append(np.floor(deg_value))
    deg_value = (deg_value - np.floor(deg_value))*60
    ans.append(np.floor(deg_value))
    return ans

sun_revs = 4320000
civ_days = 1577917500

mandocca = 78

theta_0 = lambda ahargana: ((ahargana*sun_revs/civ_days)%1)*360
theta_t = lambda ahargana, mandocca: (theta_0(ahargana) - np.rad2deg(np.arcsin((13.5/360)*np.sin(np.deg2rad(theta_0(ahargana)-mandocca)))))%360

def set_target_na_longitude(target, ahargana):
    epsilon = 0.000000001
    while np.abs(target-theta_t(ahargana)) >= epsilon:
        # print("ah=%f, tl=%f, tgt=%f"%(ahargana, theta_t(ahargana), target))
        ahargana = ahargana - (theta_t(ahargana)-target)
    return ahargana
        # print(ahargana, theta_0(ahargana), theta_t(ahargana), target-theta_t(ahargana))

def generate_vakyas(ahargana):
    tls = [0]
    v = [0]
    for i in [1,2,3,4,5]:
        tls.append(theta_t(ahargana))
        v.append(tls[i]-tls[i-1]-8)
        # print("ahargana=%f,\tml=%f\ttl=%f\tv=%f"%(ahargana, theta_0(ahargana), theta_t(ahargana), v[i]))
        print("%f,%f,%f,%f=%s"%(ahargana, theta_0(ahargana), theta_t(ahargana), v[i], to_rdm(v[i])))
        # print("ml=",to_dms(theta_0(ahargana)))
        # print("tl=",to_dms(theta_t(ahargana)))
        # print("\t\t\t\t\t\t\t\t\t\tvakya=",to_rdm(v[i]))
        ahargana = ahargana + 8

R   = 1
r0  = 3/80
Rv  = lambda ahargana, mandocca: np.sqrt(R**2-(r0*np.sin(theta_t(ahargana, mandocca)*np.pi/180-mandocca))**2)-r0*np.cos(theta_t(ahargana, mandocca)*np.pi/180-mandocca)
K   = lambda ahargana, mandocca: R**2/Rv(ahargana, mandocca)

jd_from_ag = lambda ahargana: ahargana + 588464.54
ag_from_jd = lambda jd: jd - 588464.54

moon_orb_circumference = 21600*10 #yojanas
moon_revs              = 57753336
dist_travelled_my      = moon_orb_circumference*moon_revs
sun_orb_circumference  = dist_travelled_my/sun_revs