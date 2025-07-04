package com.vt.c0605;

import android.net.NetworkInfo;
import android.telephony.TelephonyManager;
import android.util.Log;

public class Util {
    public static String getMobleType(NetworkInfo info){
        String type;
        switch (info.getSubtype()) {
            case TelephonyManager.NETWORK_TYPE_GSM:

            case TelephonyManager.NETWORK_TYPE_GPRS:
            case TelephonyManager.NETWORK_TYPE_CDMA:
            case TelephonyManager.NETWORK_TYPE_EDGE:
            case TelephonyManager.NETWORK_TYPE_1xRTT:
            case TelephonyManager.NETWORK_TYPE_IDEN:
                type = "2G";
                break;
            case TelephonyManager.NETWORK_TYPE_TD_SCDMA:
            case TelephonyManager.NETWORK_TYPE_EVDO_A:
            case TelephonyManager.NETWORK_TYPE_UMTS:
            case TelephonyManager.NETWORK_TYPE_EVDO_0:
            case TelephonyManager.NETWORK_TYPE_HSDPA:
            case TelephonyManager.NETWORK_TYPE_HSUPA:
            case TelephonyManager.NETWORK_TYPE_HSPA:
            case TelephonyManager.NETWORK_TYPE_EVDO_B:
            case TelephonyManager.NETWORK_TYPE_EHRPD:
            case TelephonyManager.NETWORK_TYPE_HSPAP:
                type = "3G";
                break;
            case TelephonyManager.NETWORK_TYPE_LTE:
            case TelephonyManager.NETWORK_TYPE_IWLAN:
                type = "4G";
                break;
            case TelephonyManager.NETWORK_TYPE_NR:
                type = "5G";
                break;
            default:
                String subtypeName = info.getSubtypeName();
                if (subtypeName.equalsIgnoreCase("TD-SCDMA")
                        || subtypeName.equalsIgnoreCase("WCDMA")
                        || subtypeName.equalsIgnoreCase("CDMA2000")) {
                    type = "3G";
                } else {
                    type = "未知";
                }
                break;
        }
        return type;
    }
}
