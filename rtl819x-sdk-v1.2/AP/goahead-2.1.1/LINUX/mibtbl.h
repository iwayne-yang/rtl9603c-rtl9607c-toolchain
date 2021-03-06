/*
 *      Include file of mibtbl.c
 *
 *      Authors: David Hsu	<davidhsu@realtek.com.tw>
 *
 *      $Id: mibtbl.h,v 1.9 2009/07/30 11:32:12 keith_huang Exp $
 *
 */

#ifndef INCLUDE_MIBTBL_H
#define INCLUDE_MIBTBL_H

#include "apmib.h"

#ifdef WIN32
#ifdef FIELD_OFFSET
#undef FIELD_OFFSET
#endif
#endif

#define FIELD_OFFSET(type, field)	((unsigned long)(long *)&(((type *)0)->field))
#define _OFFSET(field)			((int)FIELD_OFFSET(APMIB_T,field))
#define _SIZE(field)			sizeof(((APMIB_T *)0)->field)
#define _OFFSET_WLAN(field)		((int)FIELD_OFFSET(CONFIG_WLAN_SETTING_T,field))
#define _SIZE_WLAN(field)		sizeof(((CONFIG_WLAN_SETTING_T *)0)->field)

#define _OFFSET_HW(field)		((int)FIELD_OFFSET(HW_SETTING_T,field))
#define _SIZE_HW(field)			sizeof(((HW_SETTING_T *)0)->field)
#define _OFFSET_HW_WLAN(field)		((int)FIELD_OFFSET(HW_WLAN_SETTING_T,field))
#define _SIZE_HW_WLAN(field)		sizeof(((HW_WLAN_SETTING_T *)0)->field)

typedef enum { BYTE_T, WORD_T, STRING_T, BYTE5_T, BYTE6_T, BYTE13_T, IA_T, WLAC_ARRAY_T,
	DHCPRSVDIP_ARRY_T,	
#ifdef HOME_GATEWAY
		PORTFW_ARRAY_T, IPFILTER_ARRAY_T, PORTFILTER_ARRAY_T, MACFILTER_ARRAY_T, 
		URLFILTER_ARRAY_T,
		TRIGGERPORT_ARRAY_T,
#ifdef ROUTE_SUPPORT		
		STATICROUTE_ARRAY_T,
#endif		
#endif
#ifdef HOME_GATEWAY
#ifdef VPN_SUPPORT
		IPSECTUNNEL_ARRAY_T,
#endif
#endif
		DWORD_T, BYTE_ARRAY_T, 
		WDS_ARRAY_T,
#ifdef TLS_CLIENT		
		CERTROOT_ARRAY_T,
		CERTUSER_ARRAY_T,
#endif		

#if defined(GW_QOS_ENGINE) || defined(QOS_BY_BANDWIDTH)
		QOS_ARRAY_T,
#endif

//#if defined(CONFIG_RTK_MESH) && defined(_MESH_ACL_ENABLE_) Keith remove
		MESH_ACL_ARRAY_T,
//#endif

	SCHEDULE_ARRAY_T, 
#ifdef HOME_GATEWAY //defined(VLAN_CONFIG_SUPPORTED) Keith Modify
	VLANCONFIG_ARRAY_T,
#endif	
	     } TYPE_T;

// MIB value, id mapping table
typedef struct _mib_table_entry {
	int id;
	char name[32];
	TYPE_T type;
	int offset;
	int size;
} mib_table_entry_T;

extern mib_table_entry_T mib_table[], mib_wlan_table[], hwmib_table[], hwmib_wlan_table[];

#endif // INCLUDE_MIBTBL_H
