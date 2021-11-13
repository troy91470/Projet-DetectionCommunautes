#include "Graph.h"

Graph::Graph(int nbS=0)
{
    nbSommets=0;
    indexSommetMax=-1;
    listeSommets={};
    listeAdjacence={};
    AjouterSommets(nbS);
    //ctor
}

Graph::~Graph()
{
    //dtor
}

void Graph::PrintDab() {
    for (int i=0;i<indexSommetMax+1;i++) {
        if (listeSommets[i]==1) {
            cout << i << ": ";
            int siz = listeAdjacence[i].size();
            for (int j=0;j<siz;j++) {
                cout << listeAdjacence[i][j] << " ";
            }
            cout << "\n";
        }
    }
    cout << "\n";
}

int Graph::GetDegres(int index) {
    return listeAdjacence[index].size();
}

int Graph::GetNbSommets() {
    return nbSommets;
}

vector<int8_t>* Graph::GetListeSommets() {
    return &listeSommets;
}

vector<int>* Graph::GetVoisins(int indexSommet) {
    return &listeAdjacence[indexSommet];
}

void Graph::SetGraph(int indexMax,int nbS, vector<int8_t>* listeS,vector<vector<int>>* listeA) {
    indexSommetMax=indexMax;
    nbSommets=nbS;
    listeSommets.resize(indexMax+1);
    listeAdjacence.resize(indexMax+1);
    for (int i=0;i<indexSommetMax+1;i++) {
        listeSommets[i]=listeS->operator[](i);
        int taille=listeA->operator[](i).size();
        for (int j=0;j<taille;j++) {
            listeAdjacence[i].push_back(listeA->operator[](i)[j]);
        }
    }
}

void Graph::AjouterSommets(int nb) {
    for (int i=0;i<nb;i++) {
        if (indexSommetMax == nbSommets-1) {
            indexSommetMax++;
            nbSommets++;
            listeSommets.push_back(1);
            vector<int> newL;
            listeAdjacence.push_back(newL);
        }
        else {
            int out=0;
            for (int j=0;j<indexSommetMax && out==0;j++) {
                if (listeSommets[j]==0) {
                    nbSommets++;
                    listeSommets[j]=1;
                    out=1;
                }
            }
        }
    }
}

void Graph::SupprimerSommet(int index) {
    if (index > indexSommetMax || listeSommets[index]==0) {
        cout << "Le sommet n'existe pas\n";
        return;
    }
    int taille=GetDegres(index);
    for (int i=0;i<taille;i++) {
        if (listeAdjacence[index][i]!=-1) {
            SupprimerArete(index,listeAdjacence[index][i]);
        }
    }
    if (index == indexSommetMax) {
        listeSommets[index]=0;
        for (int i=index;i>-1 && listeSommets[i]==0;i--) {
            if (i==index) {
                nbSommets--;
            }
            indexSommetMax--;
            listeSommets.pop_back();
            listeAdjacence.pop_back();
        }
    }
    else {
        nbSommets--;
        listeSommets[index]=0;
        listeAdjacence[index].resize(1);
        listeAdjacence[index][0]=-1;
    }
    //cout << "Sommet supprim�\n";
}

void Graph::AjouterArete(int v1, int v2) {
    if (v1>indexSommetMax || v2>indexSommetMax || v1==v2) {
        cout << "L'ar�te ne peut pas �tre ajout�e\n";
        return;
    }
    int taille=listeAdjacence[v1].size();
    for (int i=0;i<taille;i++) {
        if (listeAdjacence[v1][i]==v2) {
            cout << "L'ar�te existe d�j�\n";
            return;
        }
    }
    listeAdjacence[v1].push_back(v2);
    listeAdjacence[v2].push_back(v1);
}

void Graph::SupprimerArete(int v1, int v2) {
    if (v1>indexSommetMax || v2>indexSommetMax || v1<0 || v2<0) {
        cout << "L'ar�te "<< v1 << " " << v2 <<" ne peut pas �tre supprim�e\n";
        return;
    }
    int out=0;
    int taille=listeAdjacence[v1].size();
    for (int i=0;i<taille && out==0;i++) {
        if (listeAdjacence[v1][i]==v2) {
            listeAdjacence[v1][i]=-1;
            //cout << "Ar�te supprim�e d'un c�t�\n";
            out=1;
        }
    }
    out=0;
    taille=listeAdjacence[v2].size();
    for (int i=0;i<taille && out==0;i++) {
        if (listeAdjacence[v2][i]==v1) {
            listeAdjacence[v2][i]=-1;
            //cout << "Ar�te supprim�e de l'autre\n";
            out=1;
        }
    }
    //cout << "Ar�te supprim�e\n";
}

void Graph::RafraichirAretes() {
    int tailleListe=listeAdjacence.size();
    int tailleSousListe;
    for (int j=0;j<tailleListe;j++) {
        tailleSousListe=GetDegres(j);
        for (int i=tailleSousListe-1;i>-1;i--) {
            vector<int>::iterator start=listeAdjacence[j].begin();
            if (listeAdjacence[j][i]==-1) {
                listeAdjacence[j].erase(start+i);
            }
        }
    }
    //cout << "Liste d'adjacence nettoy�e\n";
}

Graph* Graph::GenerateRandomGraph(int nbS, int p) {
    Graph* g = new Graph(nbS);
    std::mt19937 mt(time(nullptr));
    std::uniform_real_distribution<double> dist(1.0, 100.0);
    double r;int realr;
    for (int i=0;i<nbS;i++) {
        for (int j=i+1;j<nbS;j++) {
            r=dist(mt);r=r+0.5-(r<0);
            realr=(int)r;
            if (realr<p) {
                g->AjouterArete(i,j);
            }
        }
    }
    return g;
}

Graph* Graph::GenerateBarabasiAlbertGraph(int nbS=3, int m=0) {
    if (nbS<3) {
        Graph* g = new Graph(nbS);
        for (int i=0;i<nbS;i++) {
            for (int j=0;j<nbS;j++) {
                g->AjouterArete(i,j);
            }
        }
        return g;
    }
    else if (nbS<1) {
        return new Graph();
    }
    int compteurM=0;
    int dMax=6;int d=2;
    Graph* g = new Graph();
    g->AjouterSommets(nbS);
    g->AjouterArete(0,1);
    g->AjouterArete(0,2);
    g->AjouterArete(1,2);
    std::mt19937 mt(time(nullptr));
    std::uniform_real_distribution<double> dist(1.0, 100.0);
    double r;
    for (int i=3;i<nbS;i++) {
        for (int j=0;j<nbS&&compteurM<m;j++) {
            if (j==i) {j++;}
            d=g->GetDegres(j);
            r=dist(mt);
            if (r<(((double)d/(double)dMax)*100)) {
                g->AjouterArete(i,j);
                compteurM++;
                dMax++;
            }
        }
        compteurM=0;
    }
    return g;
}


Graph* Graph::CreerCopie() {
    Graph* g = new Graph();
    g->SetGraph(indexSommetMax,nbSommets,&listeSommets,&listeAdjacence);
    return g;
}


void Graph::sortDegenerativeList(int* tab){
	int tmp;
	int startIterator;
	int endIterator;

	for(int i=0;i<indexSommetMax+1;i++) //on parcourt la liste des sommets
	{
		int size = listeAdjacence[i].size();
		startIterator = 0;
		endIterator = size-1;

		while(startIterator != endIterator) //on parcourt les voisins du sommet actuel tant que nos 2 iterateurs sont differents
		{
			if(tab[listeAdjacence[i][startIterator]] < tab[i])
			{
				//on change la valeur placee a l'iterateur de debut, avec celle de l'iterateur de fin
				tmp = listeAdjacence[i][endIterator];
				listeAdjacence[i][endIterator] = listeAdjacence[i][startIterator];
				listeAdjacence[i][startIterator] = tmp;
				endIterator--; //on recule l'iterateur de fin
			}
			else
			{
				startIterator++; //sinon on avance l'iterateur de debut
			}
		}


	}
}



vector<int> trierVecteurSelonNum(vector<int> v) //Implementation du tri fusion
{
	if (v.size()>1) 
	{
		int mid = v.size()/2;

		vector<int> gauche(v.begin(),v.begin()+mid);
		vector<int> droite(v.begin()+mid,v.begin()+v.size());

		gauche = trierVecteurSelonNum(gauche);
		droite = trierVecteurSelonNum(droite);

		unsigned i = 0;
		unsigned j = 0;
		unsigned k = 0;
		while (i < gauche.size() && j < droite.size()) {
		    if (gauche[i] < droite[j]) {
			v[k]=gauche[i];
		        i++;
		    } else {
		        v[k] = droite[j];
		        j++;
		    }
		    k++;
		}

		while (i<gauche.size()) {
		    v[k] = gauche[i];
		    i++;
		    k++;
		}

		while (j<droite.size()) {
		    v[k]=droite[j];
		    j++;
		    k++;
        	}

    }
    return v;
}


Graph* Graph::TrouveSousGraphe(int* posOrdreDegenerescence, int numSommet){
	int i;
	int j=0;
	Graph* copieGraphe = CreerCopie();
	int size = copieGraphe->listeAdjacence[numSommet].size();
	vector<int> listeAdjTrieeParNum;

	//on redimensionne le vecteur selon la taille de la liste d'adjacence de numSommet
	listeAdjTrieeParNum.resize(size);
	
	//on copie la liste d'adjacence de numSommet dans le nouveau vecteur
	copy(copieGraphe->listeAdjacence[numSommet].begin(),copieGraphe->listeAdjacence[numSommet].end(),listeAdjTrieeParNum.begin());
	
	listeAdjTrieeParNum = trierVecteurSelonNum(listeAdjTrieeParNum);

	for(i=size-1;i>=0;i--) //on parcourt en sens inverse les voisins de numSommet
	{ 
		//si le voisin de numSommet est degenere avant numSommet, alors on supprime ce voisin
		if(posOrdreDegenerescence[listeAdjacence[numSommet][i]] < posOrdreDegenerescence[numSommet])
			copieGraphe->SupprimerSommet(copieGraphe->listeAdjacence[numSommet][i]);
		else  //sinon on a plus d'operation a faire, donc on quitte la boucle
        	{
            		break;
		}
    	}

	for(i=0;i<indexSommetMax+1;i++) //on parcourt la liste des sommets
	{
		//si le sommet parcouru n'est pas voisin de numSommet et n'est pas numSommet, alors on le supprime
		if(i != listeAdjTrieeParNum[j] && i!=numSommet)
		{
			copieGraphe->SupprimerSommet(i);
		}
		else if(i != numSommet)
		{
			j++;
		}
    	}

	copieGraphe->RafraichirAretes(); //on met a jour les aretes du sous graphe
	return copieGraphe;
}
