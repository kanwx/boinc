/* Local variables: */
/* c-file-style: "linux" */
/* End: */

#ifndef __DC_API_CONDOR_DEFS_H_
#define __DC_API_CONDOR_DEFS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <sys/time.h>
#include <uuid/uuid.h>
#include "glib.h"

#include "dc.h"
#include "dc_internal.h"


extern char project_uuid_str[37];

struct _DC_condor_event
{
	int event;
	int cluster;
	int proc;
	int subproc;
	time_t time;
	gboolean reported;
	union
	{
		struct
		{
			gboolean normal;
			int exit_code;
		} exit_info;
		struct
		{
			char *reason;
		} abort_info;
		struct
		{
			char *host;
		} exec_info;
	};
};

struct _DC_wu_data
{
	char *client_name;	// reference to the config file group
	char *tag;		// Parameter from the app
	int argc;
	int subresults;
	/*uuid_t uuid;*/
	char *uuid_str;
	char *name;		// generated by Create
	char *workdir;
	DC_WUState state;
};

struct _DC_Workunit
{
	int magic;
	struct _DC_wu_data data;
	char **argv;
    
	gboolean asked_to_suspend;

	/*char *condor_id;*/
	GArray *condor_events;
     
	GList *input_files;
	GList *output_files;
	int chk;
};

struct _DC_Result
{
	DC_Workunit *wu;
};

typedef enum
{
	FILE_IN,
	FILE_OUT,
	FILE_CKPT,
	FILE_DCAPI
} WorkdirFile;


typedef enum
{
	st_name= 0,
	st_workdir,
	st_tag,
	st_client_name,
	st_argc,
	st_argv,
	st_state,
	st_state_name
} _DC_serialized_token;


/*#define DC_LABEL_INTLOG		"internal_log.txt"*/


#ifdef __cplusplus
}
#endif

#endif

/* End of condor/condor_defs.h */
