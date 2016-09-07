#include <algorithm>
#include <utility>
#include <vector>


using namespace std;

class Node{
public:
    int  trailen;
    vector<int>  child;
    
    Node() : trailen(0)
        {}
};


int  calcam(   const int range,   const int sub_root,   vector<Node>&  node   )
{
    Node&             root =  node[sub_root];
    vector<int>&  children =  node[sub_root].child;

    // leaf node
    if(  0 == children.size()  ){
        root.trailen =  0;
        return 0;
    } // if(  0 ==  )

    int  i, cam_cnt =  0;
    for(  i = 0;  i < children.size();  ++i  ){
        cam_cnt +=  calcam( range, children[i], node );    
    }//for(i)
    
    vector<int>  ohc;
    for(  int  c = 0;  c < children.size();  ++c  ){
        ohc.push_back(  node[ children[c] ].trailen  );
    }//for(c)
    sort(  ohc.begin(),  ohc.end()  );

    for(  i = children.size()-1;   1 <= i;   --i   ){
        if(  2 + ohc[i] + ohc[i-1]  <=  range  ){
            break;
        }
        ++cam_cnt;
        ohc.erase(  ohc.begin() + i  );

    }//for( 1<=i )

    for(;   0 <= i  &&  range  <  ohc[i] + 1;   --i   ){
        ++cam_cnt;
        ohc.erase(  ohc.begin() + i  );
    }//for( 0<= )
    
    root.trailen =   0 == ohc.size()   ?   0  :  ohc.back() + 1;
    
    return  cam_cnt;
    
} //calcam(3)



int solution(  vector<int> &src,  vector<int> &dst,  int cut_num  ){

    // build up dual bi-directional tree
    const int  node_num =  src.size()+1;
    vector<Node>  node( node_num );
    for(  int i=0;   i<node_num-1;   ++i  ){
        node[ src[i] ].child.push_back(  dst[i]  );
        node[ dst[i] ].child.push_back(  src[i]  );
    }//for(i)
    
    // remove duplicated edges, pointing from CHILD to PARENT
    vector<int>  target_node( 1, src[0] );
    while(  0 < target_node.size()  ){

        int  p =  target_node.back();
        target_node.pop_back();

        for(  int i = 0;   i < node[p].child.size();   ++i  ){
            int  c =  node[p].child[i];

            vector<int>&  children =  node[c].child;
            children.erase(  find( children.begin(), children.end(), p )  );

            target_node.push_back( c );
        }//for(i)
    }//while(  0 <  )

    vector<bool>  flag( node_num, true );
    for(  int i = 0;  i<node_num;  ++i  ){
        for(  int c = 0;  c < node[i].child.size();  ++c  ){
            flag[ node[i].child[c] ] =  false;            
        }//for(c)
    }//for(i)

    int  root =  distance(  flag.begin(),  find( flag.begin(), flag.end(), true )  );
    int  lo = 0,  hi =  node_num-1,  range;
    int  minr =  node_num;

    while(  lo <= hi  ){
        range =  ( lo + hi ) / 2;
        int cam =  calcam( range, root, node );

        if(  cut_num < cam  ){
            lo =  range + 1;
        }else{
            hi =  range - 1;
            if(  range < minr )   minr =  range;
        }//else{}

    }//while( lo <= hi )

    return  minr;

}//solution(3)


int main(  int argc, char* argv[]  ){
    //int  s[] =  {5,1,0,2,7,0,6,6,1};
    //int  d[] =  {1,0,7,4,2,6,8,3,9};
    // int  s[] =  {0,1,2,3,4};
    // int  d[] =  {1,2,3,4,5};
    
    // int s[] =  {0,0,0,3};
    // int d[] =  {1,2,3,4};
    
    int  s[] =  {0,0,1,2,2,5};
    int  d[] =  {1,2,3,4,5,6};
    
    // int s[] =  {0,0,1,1,2,2};
    // int d[] =  {1,2,3,4,5,6};
    vector<int>  src(  s,  s + sizeof(s) / sizeof(int)  );
    vector<int>  dst(  d,  d + sizeof(d) / sizeof(int)  );
    
    cout << solution( src, dst, 2 );
    getchar();
    return 0;
} //main()
