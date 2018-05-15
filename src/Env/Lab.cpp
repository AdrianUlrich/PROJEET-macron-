#include "Lab.hpp"
#include <exception>
#include <Application.hpp>

Lab::Lab()
:	NTTs(0)
{
	makeBoxes(getAppConfig().simulation_lab_nb_boxes);
}

void Lab::makeBoxes(unsigned int nbCagesPerRow)
{
	if (!(boites.empty()))
		destroyBoxes();
	if (nbCagesPerRow < 1)
		throw std::invalid_argument("Cannot have zero or less cages");
	double largeur((getApp().getLabSize().x)/nbCagesPerRow);
	double hauteur((getApp().getLabSize().y)/nbCagesPerRow);
	for (unsigned int i(0); i<nbCagesPerRow; ++i)
	{
		boites.push_back(vector<Box*>(0));
		for (unsigned int j(0); j<nbCagesPerRow; ++j)
		{
			boites[i].push_back(new Box({(i+0.5)*largeur,(j+0.5)*hauteur},largeur,hauteur,largeur*0.025));
		}
	}
}

void Lab::destroyBoxes()
{
	for (auto& vec : boites)
	{
		for (auto& val : vec)
		{
			delete val;
			val=nullptr;
		}
	}
	boites.clear();
}

Lab::~Lab()
{
	reset();
	destroyBoxes();
}

void Lab::update(sf::Time dt)
{
size_t nNTTs(NTTs.size());
	for (size_t i(0); i<nNTTs; ++i)
	{//if (NTTs[i] != nullptr) // NTTs contains no nullptr
		NTTs[i]->update(dt);
		if (NTTs[i]->isDead())
		{
			/// letting other entities know of the death
			for (SimulatedEntity* val : NTTs)
			{isDead(NTTs[i]);}

			// NTTs[i]->resetBox();
			/// La boite est liberee par le destructeur de animal
			delete NTTs[i];

			/// comme les NTTs sont des pointeurs on peut les assigner
			NTTs[i]=NTTs[NTTs.size()-1];
			NTTs.pop_back();

			/// rendant ce code inutile
			//NTTs[i]=nullptr;
			//NTTs.erase(NTTs.begin()+i);

			--nNTTs;
		}
	}
}

vector<SimulatedEntity*>* Lab::findTargetInSightOf(Animal* a)
{
	vector<SimulatedEntity*>* ans(new vector<SimulatedEntity*>);
	for (auto val : NTTs)
	{//note: NTTs NEVER contains nullptrs or deleted pointers
		if
		(
			/// animal may want to see himself sometimes
			//val != a and
			/// animal may want to interact with fellow animals
			//a->eatable(val) and
			a->isTargetInSight(val->getCenter()) //and
			/// checks for closest target but animal may decide what to do with all its sights
			//((ans==nullptr) or (distance(a->getCenter(),val->getCenter()))<(distance(a->getCenter(),ans->getCenter())))
		)
			ans->push_back(val);
	}
	return ans;
}


void Lab::drawOn(sf::RenderTarget& target)
{
	for (auto& vec : boites)
	{
		for (auto val : vec)
		{
			if (val != nullptr)
				val->drawOn(target);
		}
	}
	for (auto NTT : NTTs)
	{
		NTT->drawOn(target);
	}
}

void Lab::reset()
{
	for (auto NTT/*&*/ : NTTs)
	{
		delete NTT;
		//NTT = nullptr;
	}
	NTTs.clear();
}

bool Lab::addEntity(SimulatedEntity* ntt)
{
	if (ntt==nullptr)// || NTTs.size()>100)
		return false;
	NTTs.push_back(ntt);
	return true;
}

bool Lab::addAnimal(Animal* manimal)
{
	if (manimal==nullptr) return false;
	for (auto& vec : boites)
	{
		for (auto val : vec)
		{
			if (manimal->canBeConfinedIn(val))
			{
				if (val->isEmpty())
				{
					manimal->confine(val); //! La souris est d�ja cr��e mais maintenant elle est dans une boite
					bool succ(addEntity(manimal));
					if (succ)
						val->addOccupant(); //! La boite est occupp�e
					return succ;
				}
			}
		}
	}
	delete manimal;
	return false;
}

bool Lab::addCheese(Cheese* caprice_des_dieux)
{
	return addEntity(caprice_des_dieux);
}
