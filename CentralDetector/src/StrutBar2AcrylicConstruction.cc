
#include "StrutBar2AcrylicConstruction.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"

#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/ToolFactory.h"
using namespace CLHEP;
DECLARE_TOOL(StrutBar2AcrylicConstruction);

StrutBar2AcrylicConstruction::StrutBar2AcrylicConstruction(const std::string& name)
    : ToolBase(name)
{
    logicStrut = 0;
    initVariables();

}

StrutBar2AcrylicConstruction::~StrutBar2AcrylicConstruction() {

}

G4LogicalVolume* 
StrutBar2AcrylicConstruction::getLV() {
    if (logicStrut) {
        return logicStrut;
    }
    initMaterials();

    makeStrutLogical();

    return logicStrut;
}

bool 
StrutBar2AcrylicConstruction::inject(std::string /* motherName */, IDetElement* other, IDetElementPos* pos) {
    // Get the mother volume in current DetElem.
    G4LogicalVolume* mothervol = 0;
    if (not mothervol) {
        // don't find the volume.
        return false;
    }

    // retrieve the daughter's LV
    G4LogicalVolume* daughtervol = other->getLV();

    if (not daughtervol) {
        return false;
    }

    int copyno = 0;
    while (pos->hasNext()) {
        new G4PVPlacement(
            pos->next(),
            daughtervol,
            daughtervol->GetName()+"_phys",
            mothervol,
            false,
            copyno++
                );
    }

    G4cout<< " Strut_Acrylic_Number = "<< copyno <<G4endl;
    
    return true;
}

   

void
StrutBar2AcrylicConstruction::initVariables() {

 /* m_radStrut_in  = (102./2.-12.) *mm;
  m_radStrut_out = 102./2. *mm;
  m_lengthStrut  = 1200/2.*mm;
  gap = 1 *mm;
  strut_pos = 17820. *mm + 165. *mm + m_lengthStrut;
  */
    m_radStrut_in  = 0*mm;
    m_radStrut_out = 60./2. *mm;
    m_lengthStrut  = 1525./2.*mm;
    gap = 1 *mm;
    strut_pos = 17820. *mm + 623. *mm + m_lengthStrut;


 
}

void 
StrutBar2AcrylicConstruction::initMaterials() {
    Steel = G4Material::GetMaterial("Steel");
}

void
StrutBar2AcrylicConstruction::makeStrutLogical() {
        solidStrut = new G4Tubs(
                        "sStrut",
                        m_radStrut_in,
                        m_radStrut_out,  
                        m_lengthStrut,  
                        0*deg, 
                        360*deg);


        logicStrut = new G4LogicalVolume(
                        solidStrut, 
                        Steel, 
                        "lSteel",
                        0,
                        0,
                        0);
        G4cout<< "m_radStrut = "<<m_radStrut_out<<G4endl;
        std::cout<<"this is sticks!!!!!!!!"<<std::endl;
        G4VisAttributes* strut_visatt = new G4VisAttributes(G4Colour(0, 1.0, 1.0));
        //strut_visatt -> SetForceWireframe(true);  
        //strut_visatt -> SetForceAuxEdgeVisible(true);
        strut_visatt -> SetForceSolid(true);
        // strut_visatt -> SetForceLineSegmentsPerCircle(4);
        logicStrut -> SetVisAttributes(strut_visatt);
}

