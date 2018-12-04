#pragma once
namespace binTree_modul
{
//-------------------------------------
	typedef char base;
	
	struct node {
		base info;
		node *lt;
		node *rt;
			// constructor
		node ()
		{
			lt = NULL; rt = NULL;
		}
	};
	
	typedef node *binTree; // "представитель" бинарного дерева
	binTree Create(void);
	bool isNull(binTree);
	base RootBT (binTree); // для непустого бин.дерева
	binTree Left (binTree);// для непустого бин.дерева
	binTree Right (binTree);// для непустого бин.дерева
	binTree ConsBT(const base x, binTree lst,  binTree rst);
	void destroy (binTree&);
	bool isEqual(binTree a,  binTree b);
} 
