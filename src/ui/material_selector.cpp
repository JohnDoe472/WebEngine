#include "ui/material_selector.hpp"

#include <emscripten.h>
#include <emscripten/bind.h>

namespace WebEngine::UI
{
    void MaterialSelector::addMeshes( const std::map< std::string, std::unique_ptr< Resources::Geometry::Mesh > >& meshes )
    {
        for ( const auto& mesh : meshes )
        {
            addMesh( mesh.first, mesh.second );
        }
    }

    void MaterialSelector::addMesh( const std::string& id, const std::unique_ptr< Resources::Geometry::Mesh >& mesh )
    {
        EM_ASM
        ( {
            let root = document.getElementById('meshes-list');

            let meshContainer =  document.createElement('div');
            meshContainer.setAttribute('id', UTF8ToString($0));
            meshContainer.setAttribute('class', 'mesh accordion-item');

            let meshContainerHeader = document.createElement('h2');
            meshContainerHeader.setAttribute('class', 'accordion-header');

            let meshContainerHeaderButton = document.createElement('button');
            meshContainerHeaderButton.setAttribute('class', 'accordion-button collapsed');
            meshContainerHeaderButton.setAttribute('type', 'button');
            meshContainerHeaderButton.setAttribute('data-bs-toggle', 'collapse');
            meshContainerHeaderButton.setAttribute('data-bs-target', '#' + UTF8ToString($0) + '-materialsCollapse');
            meshContainerHeaderButton.setAttribute('aria-expanded', 'false');
            meshContainerHeaderButton.setAttribute('aria-controls', UTF8ToString($0) + '-materialsCollapse');
            meshContainerHeaderButton.innerHTML = UTF8ToString($1);
            meshContainerHeader.appendChild(meshContainerHeaderButton);

            let materialsSelector = document.createElement('div');
            materialsSelector.setAttribute('id', UTF8ToString($0) + '-materialsCollapse');
            materialsSelector.setAttribute('class', 'accordion-collapse collapse');
            
            let materialsSelectorBody = document.createElement('div');
            materialsSelectorBody.setAttribute('class', 'accordion-body');
            materialsSelector.appendChild(materialsSelectorBody);

            let materialSelectorBodyContainer = document.createElement('div');
            materialSelectorBodyContainer.setAttribute('class', 'container text-center');

            let materialSelectorBodyContainerRow = document.createElement('div');
            materialSelectorBodyContainerRow.setAttribute('id', UTF8ToString($0) + '-materialsSelector');
            materialSelectorBodyContainerRow.setAttribute('class', 'row row-cols-3');

            materialSelectorBodyContainer.appendChild(materialSelectorBodyContainerRow);
            materialsSelectorBody.appendChild(materialSelectorBodyContainer);

            meshContainer.appendChild(meshContainerHeader);
            meshContainer.appendChild(materialsSelector);
            root.appendChild(meshContainer);
        }, id.c_str(), mesh->getName().c_str() );

        addMaterialForMesh( id, "default", mesh->getMaterial() );
    }

    void MaterialSelector::addMaterialForMesh( const std::string& meshID, const std::string& materialID, const std::shared_ptr< Resources::Geometry::Material >& material )
    {
        EM_ASM
        ( {
            let root = document.getElementById(UTF8ToString($0) + '-materialsSelector');

            let materialContainer = document.createElement('div');
            materialContainer.setAttribute('class', 'col');
            materialContainer.setAttribute( 'onclick', 'Module.MaterialSelector.setMaterial("' + UTF8ToString($0) + '", "' + UTF8ToString($1) + '");' );

            let materialThumbnail = document.createElement('img');
            materialThumbnail.setAttribute('src', 'resources/' + UTF8ToString($3));
            materialThumbnail.setAttribute('class', 'img-thumbnail');
            materialThumbnail.setAttribute('alt', '...');
            materialContainer.appendChild(materialThumbnail);

            let materialName = document.createElement('p');
            materialName.setAttribute('class', 'text-center text-truncate');
            materialName.innerHTML = UTF8ToString($2);
            materialContainer.appendChild(materialName);

            root.appendChild(materialContainer);
        }, meshID.c_str(), materialID.c_str(), material->getName().c_str(), material->getAlbedo()->getLocation().c_str() );
    }

    void MaterialSelector::setMaterial( std::string mesh, std::string material )
    {
        MaterialUpdateEvent.invoke( mesh, material );
    }

    void MaterialSelector::clearMeshesList()
    {
        EM_ASM
        ( {
            let parent = document.getElementById("meshes-list");
            while (parent.firstChild) {
                parent.firstChild.remove()
            }
        } );
    }

    EMSCRIPTEN_BINDINGS(material_selector)
    {
        emscripten::class_<MaterialSelector>("MaterialSelector")
            .class_function("setMaterial", MaterialSelector::setMaterial);
    }
}
