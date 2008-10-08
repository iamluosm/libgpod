/*
|  Copyright (C) 2002-2007 Jorg Schuler <jcsjcs at users sourceforge net>
|  Part of the gtkpod project.
| 
|  URL: http://www.gtkpod.org/
|  URL: http://gtkpod.sourceforge.net/
|
|  Most of the code in this file has been ported from the perl
|  script "mktunes.pl" (part of the gnupod-tools collection) written
|  by Adrian Ulrich <pab at blinkenlights.ch>.
|
|  gnupod-tools: http://www.blinkenlights.ch/cgi-bin/fm.pl?get=ipod
|
|  The code contained in this file is free software; you can redistribute
|  it and/or modify it under the terms of the GNU Lesser General Public
|  License as published by the Free Software Foundation; either version
|  2.1 of the License, or (at your option) any later version.
|
|  This file is distributed in the hope that it will be useful,
|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|  Lesser General Public License for more details.
|
|  You should have received a copy of the GNU Lesser General Public
|  License along with this code; if not, write to the Free Software
|  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
|
|  iTunes and iPod are trademarks of Apple
|
|  This product is not supported/written/published by Apple!
|
|  $Id$
*/

#ifndef __ITDB_DEVICE_H__
#define __ITDB_DEVICE_H__

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "itdb.h"
#include "itdb_sysinfo_extended_parser.h"

#include <glib.h>

G_BEGIN_DECLS

typedef enum _ItdbThumbFormat ItdbThumbFormat;

enum _ItdbThumbFormat
{
    THUMB_FORMAT_UYVY_LE,
    THUMB_FORMAT_UYVY_BE,
    THUMB_FORMAT_I420_LE,
    THUMB_FORMAT_I420_BE,
    THUMB_FORMAT_RGB565_LE,
    THUMB_FORMAT_RGB565_LE_90,
    THUMB_FORMAT_RGB565_BE,
    THUMB_FORMAT_RGB565_BE_90,
    THUMB_FORMAT_RGB555_LE,
    THUMB_FORMAT_RGB555_LE_90,
    THUMB_FORMAT_RGB555_BE,
    THUMB_FORMAT_RGB555_BE_90,
    THUMB_FORMAT_REC_RGB555_LE,
    THUMB_FORMAT_REC_RGB555_LE_90,
    THUMB_FORMAT_REC_RGB555_BE,
    THUMB_FORMAT_REC_RGB555_BE_90,
    THUMB_FORMAT_RGB888_LE,
    THUMB_FORMAT_RGB888_LE_90,
    THUMB_FORMAT_RGB888_BE,
    THUMB_FORMAT_RGB888_BE_90,
    THUMB_FORMAT_EXPERIMENTAL_LE,
    THUMB_FORMAT_EXPERIMENTAL_BE,
};

struct _Itdb_Device
{
    gchar *mountpoint;    /* mountpoint of the iPod */
    gint   musicdirs;     /* number of /iPod_Control/Music/F.. dirs */
    guint  byte_order;    /* G_LITTLE_ENDIAN "regular" endianness 
			   * G_BIG_ENDIAN "reversed" endianness (e.g. mobile
			   * phone iTunesDBs)
			   */
    GHashTable *sysinfo;  /* hash with value/key pairs of all entries
			   * in Device/SysInfo */
    SysInfoIpodProperties *sysinfo_extended; /* parsed content of 
                                              * SysInfoExtended, can be NULL */
    gboolean sysinfo_changed; /* Has the sysinfo hash been changed by
				 the user (itdb_set_sysinfo) */
    gint timezone_shift;  /* difference in seconds between the current
                           * timezone and UTC
                           */

};

struct _Itdb_ArtworkFormat {
        gint format_id;
        gint width;
        gint height;
        ItdbThumbFormat format;
        gint32 padding; /* not found in SysInfoExtended, added  
                         * for compatibility with hardcoded artwork formats */ 
        gboolean crop;
        gint rotation;
        guchar back_color[4];
 
        gint display_width;
        gboolean interlaced;
        gboolean align_row_bytes;
        gint color_adjustment;
        gdouble gamma;
        gint associated_format;
};

/* Error domain */
#define ITDB_DEVICE_ERROR itdb_device_error_quark ()
GQuark     itdb_device_error_quark      (void);

G_GNUC_INTERNAL GList *itdb_device_get_photo_formats (const Itdb_Device *device);
G_GNUC_INTERNAL GList *itdb_device_get_cover_art_formats (const Itdb_Device *device);
G_GNUC_INTERNAL gint itdb_device_musicdirs_number (Itdb_Device *device);
G_GNUC_INTERNAL void itdb_device_autodetect_endianess (Itdb_Device *device);
G_GNUC_INTERNAL guint64 itdb_device_get_firewire_id (const Itdb_Device *device);
G_GNUC_INTERNAL gboolean itdb_device_supports_sparse_artwork (const Itdb_Device *device);
G_GNUC_INTERNAL gboolean itdb_device_get_storage_info (Itdb_Device *device, guint64 *capacity, guint64 *free);
G_END_DECLS

#endif
