#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "errno.h"

#include "espectro.h"

double resistor_model();
double capacitor_model();
double inductor_model();
double voltage_source_model();
double current_source_model();
double vcvs_model();
double ccvs_model();
double vccs_model();
double cccs_model();

int source_count = 0;
Component *component_head = 0;

void print_frames();
int new_node_number();
int map_node(Value *node);

#ifndef MAXFLOAT
#define MAXFLOAT HUGE
#endif

void
add_builtin(char *name, double (*function)(char *))
{
	Symbol *new_symbol = add_symbol(name);
	new_symbol -> type = T_BUILTIN;
	new_symbol -> bound.value = new_value(T_BUILTIN);
	new_symbol -> bound.value -> v.builtin = function;
} /* end add_builtin */

void
builtin_model_init()
{
	add_builtin("resistor", &resistor_model);
	add_builtin("capacitor", &capacitor_model);
	add_builtin("inductor", &inductor_model);
	add_builtin("vsource", &voltage_source_model);
	add_builtin("isource", &current_source_model);
	add_builtin("vcvs", &vcvs_model);
	add_builtin("ccvs", &ccvs_model);
	add_builtin("vccs", &vccs_model);
	add_builtin("cccs", &cccs_model);
} /* end builtin_model_init */

void
fill_double_pairs(DoublePair pairs[])
{
	int i;
	for (i=0; pairs[i].name; i++)
		*pairs[i].var = find_symbol_double(pairs[i].name, pairs[i].default_value);
} /* end fill_double_pairs */

void
fill_int_pairs(IntPair pairs[])
{
	int i;
	for (i=0; pairs[i].name; i++)
		*pairs[i].var = find_symbol_int(pairs[i].name, pairs[i].default_value);
} /* end fill_int_pairs */

DoublePair *
copy_double_bindings(DoublePair *in)
{
	int i, length = 0;
	DoublePair *out;
	for (i = 0; in[i].name; i++) length++;
	out = (DoublePair *) malloc(length * sizeof (DoublePair));
	for (i = 0; in[i].name; i++) {
		out[i] = in[i];
		out[i].default_value = *(in[i].var);
	} /* end for */
	return(out);
} /* end copy_double_bindings */

IntPair *
copy_int_bindings(IntPair *in)
{
	int i;
	IntPair *out = (IntPair *) malloc(sizeof (in));
	for (i = 0; in[i].name; i++) {
		out[i] = in[i];
		out[i].default_value = *(in[i].var);
	} /* end for */
	return(out);
} /* end copy_int_bindings */

ExternalNode *
copy_nodes(ExternalNode in[], int count)
{
	int size = sizeof (ExternalNode) * count;
	ExternalNode *out = (ExternalNode *) malloc(size);
	memcpy(out, in, size);
	return(out);
} /* end copy_nodes */

Component *
new_component(char *component_name, int node_count)
{
	Component *new_issue;
	new_issue = (Component *) malloc(sizeof (Component));
	new_issue -> component_name = strdup(component_name); /* for shame */
	new_issue -> node_count = node_count;
	if (component_head) new_issue -> next = component_head;
	component_head = new_issue;
	return(new_issue);
} /* end new_component */

void
print_component(Component *component)
{
	int i;
	fprintf(stderr, "%s: %s(%d nodes)\n", component -> instance_name, component -> component_name, component -> node_count);
	for (i = 0; i < component -> node_count; i++)
		fprintf(stderr, "\t%s :: %d\n", component -> nodes[i].name,
			component -> nodes[i].index);
	for (i = 0; component -> bindings[i].double_pair.name; i++)
		fprintf(stderr, "\t%s = %f\n", component -> bindings[i].double_pair.name,
			component -> bindings[i].double_pair.default_value);
} /* end print_component */

void
print_components()
{
	Component *c;
	for (c = component_head; c; c = c -> next)
		print_component(c);
} /* end print_components */

double
resistor_model(Symbol *symbol)
{
	ExternalNode nodes[2] = {{ "r1", -1 }, { "r2", -1 }};
	double rv, tc, conductance;
	Component *resistor;
	DoublePair resistor_pairs[] = { { "r", &rv, 0.0 }, { "tc", &tc, 0.0 }, 0 };
	char *component_name = frame_names();
	if (debug['F']) print_frames();
	if (top_frame_size() == 2) {
		nodes[0].index = map_node(top_frame_arg(0)); 
		nodes[1].index = map_node(top_frame_arg(1));
		fprintf(stderr, "%s: resistor(%d,%d) - ", component_name, nodes[0].index, nodes[1].index);
		fill_double_pairs(resistor_pairs);
		conductance = (rv == 0.0) ? MAXFLOAT : 1.0/rv;
		fprintf(stderr, "conductance = %g\n", conductance);
		resistor = new_component("resistor", 2);
		resistor -> instance_name = component_name;
		resistor -> bindings = (Pair *) copy_double_bindings(resistor_pairs);
		resistor -> nodes = copy_nodes(nodes, 2);
	} /* end if */
	else
		warn("resistor needs 2 nodes", 0);
} /* end resistor_model */

double
capacitor_model(Symbol *symbol)
{
	ExternalNode nodes[2] = {{ "c1", -1 }, { "c2", -1 }};
	double cv, tc;
	Component *capacitor;
	DoublePair capacitor_pairs[] = { { "c", &cv, 0.0 }, { "tc", &tc, 0.0 }, 0 };
	char *component_name = frame_names();
	if (debug['F']) print_frames();
	if (top_frame_size() == 2) {
		nodes[0].index = map_node(top_frame_arg(0)); 
		nodes[1].index = map_node(top_frame_arg(1));
		fprintf(stderr, "%s: capacitor(%d,%d) - ", component_name, nodes[0].index, nodes[1].index);
		fill_double_pairs(capacitor_pairs);
		fprintf(stderr, "capacitance = %g\n", cv);
		capacitor = new_component("capacitor", 2);
		capacitor -> instance_name = component_name;
		capacitor -> bindings = (Pair *) copy_double_bindings(capacitor_pairs);
		capacitor -> nodes = copy_nodes(nodes, 2);
	} /* end if */
	else
		warn("capacitor needs 2 nodes", 0);
} /* end capacitor_model */

double
inductor_model(Symbol *symbol)
{
	ExternalNode nodes[3] = {{ "l1", -1 }, { "l2", -1 }, {"l3", -1}};
	double lv, tc;
	Component *inductor;
	DoublePair inductor_pairs[] = { { "l", &lv, 0.0 }, { "tc", &tc, 0.0 }, 0 };
	char *component_name = frame_names();
	if (debug['F']) print_frames();
	if (top_frame_size() == 2) {
		nodes[0].index = map_node(top_frame_arg(0)); 
		nodes[1].index = map_node(top_frame_arg(1));
		fprintf(stderr, "%s: inductor(%d,%d) - ", component_name, nodes[0].index, nodes[1].index);
		nodes[2].index = new_node_number();
		fill_double_pairs(inductor_pairs);
		fprintf(stderr, "inductance = %g\n", lv);
		inductor = new_component("inductor", 2);
		inductor -> instance_name = component_name;
		inductor -> bindings = (Pair *) copy_double_bindings(inductor_pairs);
		inductor -> nodes = copy_nodes(nodes, 2);
	} /* end if */
	else
		warn("inductor needs 2 nodes", 0);
} /* end inductor_model */

double
voltage_source_model(Symbol *symbol)
{
	int node1, node2, node3, snode;
	double v;
	DoublePair vs_pairs[] = { { "v", &v, 0.0 }, 0 };
	if (top_frame_size() == 2) {
		node1 = map_node(top_frame_arg(0)); 
		node2 = map_node(top_frame_arg(1));
		fprintf(stderr, "voltage_source(%d,%d) - ", node1, node2);
		node3 = new_node_number();
		fill_double_pairs(vs_pairs);
		fprintf(stderr, "source = %g\n", v);
		snode = source_count++;
	} /* end if */
	else
		warn("voltage source needs 2 nodes", 0);
} /* end voltage_source_model */

double
current_source_model(Symbol *symbol)
{
	int node1, node2, snode;
	double i;
	DoublePair cs_pairs[] = { { "i", &i, 0.0 }, 0 };
	if (top_frame_size() == 2) {
		node1 = map_node(top_frame_arg(0)); 
		node2 = map_node(top_frame_arg(1));
		fprintf(stderr, "current_source(%d,%d) - ", node1, node2);
		fill_double_pairs(cs_pairs);
		fprintf(stderr, "source = %g\n", i);
		snode = source_count++;
	} /* end if */
	else
		warn("current source needs 2 nodes", 0);
} /* end current_source_model */

double
vcvs_model(Symbol *symbol)
{
	int node1, node2, node3, node4, node5;
	double g;
	DoublePair vcvs_pairs[] = { { "g", &g, 0.0 }, 0 };
	if (top_frame_size() == 4) {
		node1 = map_node(top_frame_arg(0)); 
		node2 = map_node(top_frame_arg(1));
		node3 = map_node(top_frame_arg(2)); 
		node4 = map_node(top_frame_arg(3));
		fprintf(stderr, "vcvs(%d,%d,%d,%d) - ", node1, node2, node3, node4);
		fill_double_pairs(vcvs_pairs);
		fprintf(stderr, "source = %g\n", g);
		node5 = new_node_number();
	} /* end if */
	else
		warn("voltage controlled current source needs 4 nodes", 0);
} /* end vcvs_model */

double
ccvs_model(Symbol *symbol)
{
	int node1, node2, node3, node4;
	double g;
	DoublePair ccvs_pairs[] = { { "g", &g, 0.0 }, 0 };
	if (top_frame_size() == 3) {
		node1 = map_node(top_frame_arg(0)); 
		node2 = map_node(top_frame_arg(1));
		node3 = map_node(top_frame_arg(2)); 
		fprintf(stderr, "ccvs(%d,%d,%d) - ", node1, node2, node3);
		fill_double_pairs(ccvs_pairs);
		fprintf(stderr, "source = %g\n", g);
		node4 = new_node_number();
	} /* end if */
	else
		warn("current controlled voltage source needs 4 nodes", 0);
} /* end ccvs_model */

double
vccs_model(Symbol *symbol)
{
	int node1, node2, node3, node4;
	double g;
	DoublePair vccs_pairs[] = { { "g", &g, 0.0 }, 0 };
	if (top_frame_size() == 4) {
		node1 = map_node(top_frame_arg(0)); 
		node2 = map_node(top_frame_arg(1));
		node3 = map_node(top_frame_arg(2)); 
		node4 = map_node(top_frame_arg(3)); 
		fprintf(stderr, "vccs(%d,%d,%d,%d) - ", node1, node2, node3, node4);
		fill_double_pairs(vccs_pairs);
		fprintf(stderr, "source = %g\n", g);
	} /* end if */
	else
		warn("voltage controlled current source needs 4 nodes", 0);
} /* end vccs_model */

double
cccs_model(Symbol *symbol)
{
	int node1, node2, node3;
	double g;
	DoublePair cccs_pairs[] = { { "g", &g, 0.0 }, 0 };
	if (top_frame_size() == 3) {
		node1 = map_node(top_frame_arg(0)); 
		node2 = map_node(top_frame_arg(1));
		fprintf(stderr, "cccs(%d,%d) - ", node1, node2);
		fill_double_pairs(cccs_pairs);
		fprintf(stderr, "source = %g\n", g);
		node3 = new_node_number();
	} /* end if */
	else
		warn("current controlled current source needs 4 nodes", 0);
} /* end cccs_model */

