#ifndef ORGAN_HPP
#define ORGAN_HPP

#include "Substance.hpp"

#include <SFML/Graphics.hpp>
#include <Application.hpp>
#include <Utility/Utility.hpp>
#include <Types.hpp>

#include <vector>
using std::vector;

class CellHandler;


class Organ 
{
	public:
		enum class Kind : short {ECM,Liver,Artery,Capillary};
		
	public:
		Organ(bool generation);
		
		virtual ~Organ() = default;
		
		void update();
		void drawOn(sf::RenderTarget& target);
		
		/** simply return config size of organ */
		double getWidth() const;
		double getHeight() const;
		
		bool isOut(CellCoord const&) const;
		virtual CellCoord toCellCoord(Vec2d const&) const;

		void updateRepresentation(bool b=true);
		virtual void updateRepresentationAt(CellCoord const&);
		
		void updateCellHandlerAt(CellCoord const&, Substance const&);
		double getConcentrationAt(CellCoord const&,SubstanceId) const;
		
		void setSubstance(SubstanceId const& id);
		
	protected:
		virtual void generate();
		void reloadConfig();
		void reloadCacheStructure();
		
		void createLiver();
		
		void createBloodSystem(bool generateCapillaries=true);
		virtual void generateArtery(int,int);
		virtual bool generateCapillaryOneStep(CellCoord& p, CellCoord const& dir, int& NBcells, int const& maxLength);
		virtual void generateCapillaryFromPosition(CellCoord& p, CellCoord dir);
		
		virtual void updateCellHandler(CellCoord const&,Kind);

	private:
		void drawRepresentation();
		
	private:		
		int nbCells;
		float cellSize;
		sf::RenderTexture renderingCache;
		vector<vector<CellHandler*>> cellHandlers;
		vector<sf::Vertex> bloodVertexes;
		vector<sf::Vertex> liverVertexes;
		vector<sf::Vertex> concentrationVertexes;
		
		SubstanceId currentSubst;
};

#endif // ORGAN_HPP
