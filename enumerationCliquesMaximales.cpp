#include "BronKerbosch.cpp"
#include "TableauSuffixes.h"

bool verifClique(Graph graph,vector<int> K,int ordreDegenerescence[],int sommetSousGraphe,int sommetEtude);


vector<vector<int>> listeCliquesEnumAlgo1(Graph graph)
{
	int i,j;
	int posSommetOrdreDegenerescence[graph.GetNbSommets()];
	vector<vector<int>> listeCliquesEnum, maxClique;
	vector<int> vectOrdreDegenerescence;

	ordreDegenerescence(graph, vectOrdreDegenerescence, posSommetOrdreDegenerescence);
	sortDegenerativeList(posSommetOrdreDegenerescence);
	TableauSuffix T = TableauSuffix();

	for(i=0;i<graph.GetNbSommets();i++)
	{
		maxClique = BronKerboschDegeneracy(graph);
		for(j=0;j<maxClique.size();j++)
		{
			if(T.rechercheSuffix(maxClique[j]))
				//RIEN
			else
			{
				T.ajoutVecteur(maxClique[j]);
				T.creerTableau();
				listeCliquesEnum.push_back(maxClique[j]);
			}
		}
		graph = graph->TrouveSousGraphe(posOrdreDegenerescence, i);
	}
	return listeCliquesEnum;
}


vector<vector<int>> listeCliquesEnumAlgo2(Graph graph)
{
	int i, j, z;
	bool aAjouter = true;
	int posSommetOrdreDegenerescence[graph.GetNbSommets()];
	vector<vector<int>> listeCliquesEnum, maxCliques;
	vector<int> vectOrdreDegenerescence;

	ordreDegenerescence(graph, vectOrdreDegenerescence, posSommetOrdreDegenerescence);
	sortDegenerativeList(posSommetOrdreDegenerescence);

	for(i=0;i<graph.GetNbSommets();i++)
	{
		Graph Gi = sousgraphe(posSommetOrdreDegenerescence[i]);
		maxCliques = BronKerboschDegeneracy(Gi);
		for(j=0;j<maxCliques.size();j++)
		{
			for(z=0;z<maxCliques[j].size();z++)
			{
				if(verifClique(&graph,maxCliques[j],posSommetOrdreDegenerescence,posSommetOrdreDegenerescence[i],z))
				{
					aAjouter = false;
					break;
				}
				else
				{
					//RIEN
				}
			}
			if(aAjouter)
			{
				listeCliquesEnum.push_back(maxCliques[i]);
			}
			else
			{
				//RIEN
			}
		}
	}
	return listeCliquesEnum;
}

bool verifClique(Graph* graph,vector<int> K,int ordreDegenerescence[],int sommetSousGraphe,int sommetEtude)
{
	vector<int>* voisinsDeSommetEtude = graph->GetVoisins(sommetEtude);
	vector<int>* voisinsDeVoisins;
	vector<int> intersection;

	for (int i = 0; i < voisinsDeSommetEtude->size(); i++)
	{
		if(ordreDegenerescence[i] < ordreDegenerescence[sommetSousGraphe])
		{
			//Suppose que K et voisinsDeVoisins sont triees de la même maniere.
			K = trierVecteurSelonOrdre(K,ordreDegenerescence,graph->GetNbSommets());
			voisinsDeVoisins = graph->GetVoisins(i);// IF neighbors of X adjacent to all vertex of K
			*voisinsDeVoisins = trierVecteurSelonOrdre(*voisinsDeVoisins,ordreDegenerescence,graph->GetNbSommets());
			set_intersection(voisinsDeVoisins->begin(),voisinsDeVoisins->end(),K.begin(),K.end(),back_inserter(intersection));
			if (intersection.size() == K.size()) // if intersection == K
			{
				return false;
			}
		}
		else
		{
			continue;
		}
	}
	return true;
}


int main(){

	return 0;
}



