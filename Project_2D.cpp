#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

/////////////// Global Variable /////////////////
const int n=100;
float mat[n][n];

////////////// Structures /////////////////////

//for storing the point in 2-D
struct value
{
	int x;
	int y;
};

//for vertex information of a graph/tree
struct Graph
{
	int v;
	float key;
	Graph* p;
};

//for linklist of Graph
struct Graph_Node
{
	Graph* data;    // we are taking address oterwise changes in graph won't reflect in queue
	Graph_Node* next;
};

//for storing the clusters
struct cl_Node
{
	Graph_Node* g;
	cl_Node* cl_next;
};

///////////////////// functions///////////////
void print_all_cluster(cl_Node* F);
/// function for cl_node ///

cl_Node* create_cl_node(Graph_Node* a)
{
	cl_Node* temp = new cl_Node;
	temp->g = a;
	temp->cl_next = 0;
}

void insert_cl_node(cl_Node** F, Graph_Node* a)
{
	cl_Node* ins = create_cl_node(a);
	
	if(*F == 0)
	*F = ins;
	else
	{
		cl_Node* P = *F;
		while(P->cl_next != 0)
		P = P->cl_next;
		
		P->cl_next = ins;
	}
}

cl_Node* search_cl_node(cl_Node* c, Graph_Node* s)
{
	if(c == 0)
	return 0;
	else
	{
		if(c->g==s)
		return c;
		else
		{
			while(c->cl_next != 0)
			{
				if(c->cl_next->g == s)
				return c;
				
				c = c->cl_next;
			}
			return 0;
		}	
	}	
}

void delete_cl_node(cl_Node** F, Graph_Node* g_n)
{
	cl_Node* S =  search_cl_node(*F,g_n);
	if((*F)->g== g_n)
	{
		*F = (*F)->cl_next;
	}
	else
	{
		S->cl_next = S->cl_next->cl_next;
	}
}

//////functions for adj_mat making//////

float weight(value a, value b)
{
	return sqrt(pow((a.x - b.x),2) +pow((a.y - b.y),2));
}

void make_adj_mat(value* d)
{
	for(int i=0; i<n; i++)
	{
		
		for(int j=0; j<n; j++)
		{
			mat[i][j] = weight(d[i],d[j]);
			
		}
	}
}

void print_mat()
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cout << mat[i][j]<<" ";
		}
		cout <<endl;
	}
}

/////////// function for MST making ////////////
//////function for queue///////

Graph_Node* Create_node(Graph* d)
{
	Graph_Node* A = new Graph_Node;
	A->data = d;
	A->next = 0;
	return  A;
}

Graph_Node* search_node(Graph_Node* F, Graph* s)
{
	if(F == 0)
	return 0;
	else
	{
		if(F->data->v==s->v)
		return F;
		else
		{
			while(F->next != 0)
			{
				if(F->next->data->v == s->v)
				return F;
				
				F = F->next;
			}
			return 0;
		}	
	}	
}

void delete_node(Graph_Node** F, Graph* d)
{
	Graph_Node* S = search_node(*F, d);
	if((*F)->data->v == d->v)
	{
		*F = (*F)->next;
		//delete S;
	}
	else
	{
		Graph_Node* temp1 = S->next;
		S->next = S->next->next;
		//delete temp1;
	}
}


void Enqueue(Graph_Node** F, Graph* d)
{
	Graph_Node* ins = Create_node(d);
	
	if(*F == 0)
	*F = ins;
	else
	{
		Graph_Node* P = *F;
		while(P->next != 0)
		P = P->next;
		
		P->next = ins;
	}
}

Graph_Node* Dequeue(Graph_Node** F)
{
	Graph_Node* p = *F;
	Graph_Node* min = p;
	while(p != 0)
	{
		if(p->data->key < min->data->key )
		min = p;
		
		p = p->next;
	}
	Graph_Node* temp = min;
	delete_node(F,temp->data);
	return min;
}

void print(Graph_Node* F)
{
	while(F != 0)
	{
		cout << F->data->v<< " ";
		F= F->next;
	}
	cout <<endl;
}

/////////////////////////

bool in_queue(Graph_Node* Qe, Graph* s)
{
	Graph_Node* se = search_node(Qe, s);
	if(se == 0)
	return false;
	else
	return true;
}

void MST_prim(Graph* Gr, int r)
{
	// assigning the attribute to graph node
	for(int i=0; i<n; i++)
	{
		Gr[i].key = INT_MAX;
		Gr[i].p = 0;
	}
	Gr[r].key = 0;
	
	//makin priority Queue
	Graph_Node* Q = 0;
	for(int i=0; i<n; i++)
	{
		Enqueue(&Q, &Gr[i]);
	}
	
	while(Q != 0)
	{		
		Graph* u = Dequeue(&Q)->data;
		for(int i=0; i<n; i++)      //as our graph is complete graph all the edges are adjency edge
		{
			if(in_queue(Q, &Gr[i]) && mat[u->v][Gr[i].v] < Gr[i].key)
			{
				Gr[i].p = u;
				Gr[i].key = mat[u->v][Gr[i].v];				
			}
		}
	}
}

Graph* copy_Graph(Graph* Gr)
{
	Graph* P = new Graph[n];
	for(int i=0; i<n; i++)
	{
		P[i] = Gr[i];
	}
	return P;
}

void print_graph(Graph* Gr)
{
	for(int i=0; i<n; i++)
	{
		if(Gr[i].p != 0)
		cout <<"v= "<<Gr[i].v<<" key= "<<Gr[i].key<<" p="<<Gr[i].p->v<<endl;
		else 
		cout <<"v= "<<Gr[i].v<<" key= "<<Gr[i].key<<" p="<<"null"<<endl;
	}
}

////////////////////////////////////////////////

////////// function for linklist of graph ///////
void create_graph_link_arr(Graph_Node** K, Graph* Gr, int r)
{
	for(int i=0;i<n; i++)
	{
		if(Gr[i].p != 0 && (Gr[i].p)->v == r)
		Enqueue(K, &Gr[i]), create_graph_link_arr(K, Gr, Gr[i].v);
	}
	return;
}


void print_graph_link(Graph_Node* F)
{
	while(F != 0)
	{
		if(F->data->p != 0)
		cout<<"(" <<F->data->v<< ","<<F->data->key<<","<<F->data->p->v<<")", F = F->next;
		else
		cout<<"(" <<F->data->v<< ","<<F->data->key<<","<<"na"<<")", F = F->next;
	}
	
	cout <<endl;
}

///////////////// clustring function //////////

int max_weight(Graph* cl)
{
	int max = 0;
	for(int i=0; i<n; i++)
	{
		if(cl[i].key > cl[max].key)
		max = i;
	}
	return max;
}

void edge_remove(Graph* cl, int* root, int* top)
{
	int m = max_weight(cl);
	root[*top] = m;
	cl[m].key =0;
	cl[m].p = 0;
	*top = *top +1;
}



/////// clustring based on number of clusters ///////
cl_Node* cluster_base_on_number(Graph* Gr, int no)
{
	Graph* cl = copy_Graph(Gr);
	if(no > n)
	cout << "no is more then no of vertix taking the no equal to no of vertix"<<endl, no = n;
	
	int r[no];
	r[0] = 0;
	int top=1;
	for(int i=0; i<no-1; i++)
	{
		edge_remove(cl, r, &top);
	}
	
	cl_Node* cl_set = 0;
	Graph_Node* cl_1 = 0;
	for(int i=0; i<top; i++)
	{
		cl_1 = 0;
		cl_1 = Create_node(&cl[r[i]]);
		create_graph_link_arr(&cl_1, cl, r[i]);
		insert_cl_node(&cl_set, cl_1);
	}
	
	return cl_set;
}

void cluster_number_print(Graph* Gr, int no)
{
	cl_Node* C_no_set = cluster_base_on_number(Gr, no);
	cout << "cluster based on number are : "<<endl;
	print_all_cluster(C_no_set);
}

////////// cluster based on threshold ///////////
cl_Node* cluster_base_on_threshold(Graph* Gr, float th)
{
	Graph* cl = copy_Graph(Gr);
	int r[n];
	r[0] = 0;
	int top=1;
	while(cl[max_weight(cl)].key > th)
	{
		edge_remove(cl, r, &top );
	}
	
	cl_Node* cl_set = 0;
	for(int i=0; i<top; i++)
	{
		Graph_Node* cl_1 = 0;
		cl_1 = Create_node(&cl[r[i]]);
		create_graph_link_arr(&cl_1, cl, r[i]);
		insert_cl_node(&cl_set, cl_1);
 }
	return cl_set;
}

void cluster_threshold_print(Graph* Gr, float t)
{
	cl_Node* C_t_set = cluster_base_on_threshold(Gr, t);
	cout << "cluster based on threshold are : "<<endl;
	print_all_cluster(C_t_set);
}

//// clustring based on density /////

int count_points(Graph_Node* N)
{
	int c=0;
	while(N != 0)
	c= c+1, N= N->next;
	
	return c;
}

bool is_equal(cl_Node* cl_s)
{
	bool flag = false;
	cl_Node* q = cl_s;
	if(q == 0)
	{
		return false;
	}
	
	else if(q->cl_next == 0)
	{
		return false;
	}
	
	else
	{
		while(q ->cl_next != 0)
		{	
			if( count_points(q->g) == count_points(q->cl_next->g))
			flag = true, q= q->cl_next;
			else
			return false;
		}	
		return flag;
	}	
}

Graph_Node* max_size_cluster(cl_Node* cl_s)
{
	if(cl_s == 0)
	return 0;
	else
	{
		cl_Node* q = cl_s;
		Graph_Node* max_node = q->g;
		while(q != 0)
		{
			if(count_points(q->g) > count_points(max_node))
			max_node = q->g;
			
			q= q->cl_next;	
		} 
		return max_node;
	}	
}

void create_graph_link(Graph_Node** K, Graph_Node* cl, int r)  //can we use dP?
{
	Graph_Node* q = cl;
	while(q != 0)
	{
		if(q->data->p != 0 && q->data->p->v == r)
		Enqueue(K, q->data), create_graph_link(K, q, q->data->v);
		
		q = q->next;
	}
	return;
}

Graph* max_weight(Graph_Node* cl)
{
	Graph_Node* p = cl;
	Graph* max = p->data;
	while(p != 0)
	{
		if(p->data->key > max->key)
		max = p->data;
		
		p=p->next;
	}
	return max;
}

Graph* edge_remove(Graph_Node* cl)
{
	Graph* m = max_weight(cl);
	m->key = 0;
	m->p = 0;
	return m;
}


void divide_cluster(cl_Node** cl_s, Graph_Node* g_n)
{
	Graph* m_g = edge_remove(g_n);
	
	Graph_Node* g_1 =0;
	g_1 = Create_node(g_n->data);
	create_graph_link(&g_1, g_n, g_n->data->v);
	insert_cl_node(cl_s,g_1);
	
	Graph_Node* g_2 =0;
	g_2 = Create_node(m_g);
	create_graph_link(&g_2, g_n, m_g->v);
	insert_cl_node(cl_s,g_2);
	
	delete_cl_node(cl_s, g_n);	
}

cl_Node* cluster_based_on_density(Graph* Gr)
{
	Graph* R = copy_Graph(Gr);
	
	cl_Node* cl_s = 0;
	Graph_Node* C = 0;
	C = Create_node(&R[0]);
	create_graph_link_arr(&C, R, 0);
	insert_cl_node(&cl_s,C);
	
	while(is_equal(cl_s) == false)
	{
		Graph_Node*  max_node= max_size_cluster(cl_s);
		divide_cluster(&cl_s, max_node);
	}
 	return cl_s;
}

void cluster_density_print(Graph* Gr)
{
	
	cl_Node* cl_set = cluster_based_on_density(Gr);
	cout << "clustring based on density is : "<<endl;
	print_all_cluster(cl_set);
}


////////// menue driven clustring ////////////
void menue_driven_clustring(Graph* Gr)
{
	char user_input;
	cout <<"enter integer to stop: "<<endl;
	do
	{
		cout << "on what base you want to do clustring "<<endl;
		cout << "press 'a' for based on no of clusters :"<<endl;
		cout << "press 'b' for based on threshold : " << endl;
		cout << "press 'c' for based on density: "<<endl;
		cin >> user_input;
		
		if(user_input == 'a')
		{
			int no_cluster;
			cout << "enter the number of cluster you want : (PLEASE input integer only)";
			cin >> no_cluster;
			cluster_number_print(Gr, no_cluster);
		}
		
		else if(user_input == 'b')
		{
			float thr;
			cout << "enter the threshold (in float) : ";
			cin >> thr;
			cluster_threshold_print(Gr, thr);
		}
		
		else if(user_input == 'c')
		{
			cluster_density_print(Gr);
		}
		else
		{
			cout<<"wrong input, input again...."<<endl;
			continue;
		}
	}while(user_input);
}

void print_all_cluster(cl_Node* F)
{
	int i=1;
	while(F!= 0)
	{
		cout << "cluster "<<i <<" is (v,k,p): ";
		print_graph_link(F->g);
		F= F->cl_next;
		i++;
	}
	cout <<endl;
}

int main()
{
	// storning the data
	//int X[n] = { 3, 7, 11, 15, 17, 23, 25, 45, 67, 43, 12, 34, 38, 29, 49, 53, 41, 73, 92, 4, 57, 43, 88, 91, 95};
	//int Y[n] = { 5, 8, 12, 21, 6, 19, 32, 56, 73, 80, 56, 48, 52, 24, 73, 32, 67, 63, 88, 77, 85, 98 ,79, 96, 34};
	int X[n];
	int Y[n];
	for(int i=0; i<n; i++)
	{
		X[i] = rand();
		Y[i] = rand();
	}
	
	value data[n];
	for(int i=0; i<n; i++)
	{
		data[i].x = X[i];
		data[i].y = Y[i];
	}
	
	
	/////// making graph ///////
	Graph G[n];
	for(int i=0; i<n; i++)
	{
		G[i].v = i;
	}
	
	//making the adjecency matrix
	make_adj_mat(data);
	//print_mat();
	
	//////////making MST /////////
	MST_prim(G,0);
	print_graph(G);
	
	
	
	//////// clustring ///////
	// clustring based on number
	//cluster_number_print(G,6);
	
	// clustring based on threshold
	//cluster_threshold_print(G, 10);
	
	//clustring based on density
	//cluster_density_print(G);
	
	
	
	// menue driven clustring
	menue_driven_clustring(G);

}


