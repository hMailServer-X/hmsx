#include "pch.h"
#include "Mime.h"

namespace HM
{

   const char* MimeHeader::type_table_[] =
   {
	   "text", "image", "audio", "video", "application", "multipart", "message", NULL
   };

   const MimeHeader::MediaTypeCvt MimeHeader::type_cvt_table_[] =
   {
	   // media-type, sub-type, file extension
	   { MEDIA_APPLICATION, "xml", "xml" },
	   { MEDIA_APPLICATION, "msword", "doc" },
	   { MEDIA_APPLICATION, "rtf", "rtf" },
	   { MEDIA_APPLICATION, "vnd.ms-excel", "xls" },
	   { MEDIA_APPLICATION, "vnd.ms-powerpoint", "ppt" },
	   { MEDIA_APPLICATION, "pdf", "pdf" },
	   { MEDIA_APPLICATION, "zip", "zip" },

	   { MEDIA_IMAGE, "jpeg", "jpeg" },
	   { MEDIA_IMAGE, "jpeg", "jpg" },
	   { MEDIA_IMAGE, "gif", "gif" },
	   { MEDIA_IMAGE, "tiff", "tif" },
	   { MEDIA_IMAGE, "tiff", "tiff" },

	   { MEDIA_AUDIO, "basic", "wav" },
	   { MEDIA_AUDIO, "basic", "mp3" },

	   { MEDIA_VIDEO, "mpeg", "mpg" },
	   { MEDIA_VIDEO, "mpeg", "mpeg" },

	   { MEDIA_UNKNOWN, "", "" }		// add new subtypes before this line
   };
}
