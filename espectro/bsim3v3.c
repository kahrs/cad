#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errno.h"

#include "espectro.h"

void
bsim3v3()
{
	int node_d, node_g1, node_s, node_b;
	int frame;
	double s;
	if (instance_frame_size() == 4) {
		node_d = map_node(instance_frame_arg(0)); 
		node_g1 = map_node(instance_frame_arg(1));
		node_s = map_node(instance_frame_arg(2));
		node_b = map_node(instance_frame_arg(3));
print_frames();
		fprintf(stderr, "bsim3(%d,%d,%d,%d) - ", node_d, node_g1, node_s, node_b);
		/*getparams();*/
	} /* end if */
	else
		warn("bsim3 model requires 4 nodes", 0);
} /* end bsim3v3 */

