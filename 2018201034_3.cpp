/*
 * EXTERNAL SORT by Rushit M Jasani : 2018201034
 */

#include<bits/stdc++.h>
using namespace std;
#define RUN_SIZE 1000000

int min_heap[1000000];
int file_index[1000000];

/*
 * Heapify in MinHeap
 */
void Min_Heapify(int index, int size)
{
    int left_child = (2 * index) + 1;
    int right_child = (2 * index) + 2;
    int min_pos;
    if (left_child <= size - 1 && min_heap[left_child] < min_heap[index])
        min_pos = left_child;
    else
        min_pos = index;

    if (right_child <= size - 1 && min_heap[right_child] < min_heap[min_pos])
        min_pos = right_child;

    if (min_pos != index)
    {
        int temp = min_heap[index];
        min_heap[index] = min_heap[min_pos];
        min_heap[min_pos] = temp;

        int temp1 = file_index[index];
        file_index[index] = file_index[min_pos];
        file_index[min_pos] = temp1;
        Min_Heapify(min_pos, size);
    }
    return;
}

void create_heap(int size){
    for(int i = (size/2) + 2; i>=0;i--){
        Min_Heapify(i,size);
    }
}

void k_way_merge(char *out_file,int num_of_runs){
    ofstream final_out;
    final_out.open(out_file);
    vector< ifstream > chunks(num_of_runs);
    for(unsigned int i=0;i<chunks.size();i++){
        string f_name = to_string(i);
        chunks[i].open(f_name);
    }
    int min_heap_size = num_of_runs;
    for(unsigned int i=0;i<chunks.size();i++){
        int tmp;
        if(chunks[i] >> tmp){
            min_heap[i] = tmp;
            file_index[i] = i;
        } 
    }
    create_heap(min_heap_size);
    int iterator = 0;
    while(iterator != num_of_runs){

        final_out << min_heap[0] << endl;
        int tmp_data;
        if(chunks[file_index[0]] >> tmp_data){
            min_heap[0] = tmp_data;
        }
        else{
            min_heap[0] = INT_MAX;
            iterator++;
        }
        Min_Heapify(0,min_heap_size);
    }
    for(unsigned int i=0;i<chunks.size();i++){
        chunks[i].close();
        string s = to_string(i);
        remove( s.c_str() );
    }
    final_out.close();
}

void external_merge(char *inp_file, char *out_file){
    ifstream inp;
    inp.open(inp_file);
    int data;
    int count=RUN_SIZE;
    int int_file_name = 0;
    string f_name;
    ofstream outfile;
    vector<int> v;
    while(inp >> data){
        if(count == RUN_SIZE){
            f_name = to_string(int_file_name);
            int_file_name++;
            v.clear();
            outfile.open(f_name);
        }
        v.push_back(data);
        count--;
        if(count == 0){
            sort(v.begin(),v.end());
            for(unsigned int i=0;i<v.size();i++) outfile << v[i] << endl;
            outfile.close();
            count = RUN_SIZE;
        }
    }
    if(count != RUN_SIZE){
            sort(v.begin(),v.end());
            for(unsigned int i=0;i<v.size();i++) outfile << v[i] << endl;
            outfile.close();
            count = RUN_SIZE;
    }
    int num_of_runs = int_file_name;
    inp.close();

    /*
     * Merging sorted chunks
     */
    k_way_merge(out_file, num_of_runs);
}

int main(int argc, char * argv[]){
    ios_base::sync_with_stdio(false);
    if(argc != 3){
        cout << "Invalid arguments" << endl;
        exit(0);
    }
    else{
        external_merge(argv[1], argv[2]);
    }
    cout<<"\nTime Elapsed: " << 1.0*clock() / CLOCKS_PER_SEC << " sec\n";
    return 0;
}