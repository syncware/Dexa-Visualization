#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include <math.h>
#include <tuple>
#include "Model.h"

using namespace std;

class AssetExplorerGeneration {

    public:
        AssetExplorerGeneration();
        ~AssetExplorerGeneration();
        tuple<vector<string>, vector<string>, vector<string>> GetUniqueData(vector<ProductionData>& productionDataList);
        bool IsContains(vector<string>& texts, string& text);
        vector<FieldProductionData> CreateAssetsExplorer(vector<ProductionData>& productionDataList);
        string GetRow(ProductionData& r, bool& isLastRow);
};

AssetExplorerGeneration::AssetExplorerGeneration(){

}

AssetExplorerGeneration::~AssetExplorerGeneration(){

}

bool AssetExplorerGeneration::IsContains(vector<string>& texts, string& text)
{
	bool check = false;
	int datessize = texts.size();
	for (int i = 0; i < datessize; i++)
	{
		if (texts[i] == text)
		{
			check = true; break;
		}
	}

	return check;
}


string AssetExplorerGeneration::GetRow(ProductionData& r, bool& isLastRow){

string row = "";
string columnDelimeter = "@#$%";
string rowDelimeter = "@#*$%";

std::string uniqueId = r.drainagePoint + r.reservoir + r.field + r.lease;

string lastrow = std::to_string(r.year) +  rowDelimeter;
if(isLastRow == true){
	lastrow = std::to_string(r.year); // no new line
}


row = uniqueId +  columnDelimeter
		+ std::to_string(r.condensateGasRatio) +  columnDelimeter
		+ std::to_string(r.cumulativeGasInjected) +  columnDelimeter
		+ std::to_string(r.cumulativeOilProduced) +  columnDelimeter
		+ std::to_string(r.day) +  columnDelimeter
		+ r.drainagePoint +  columnDelimeter
		+ r.field +  columnDelimeter
		+ r.lease +  columnDelimeter
		+ std::to_string(r.month) +  columnDelimeter
		+ std::to_string(r.monthlyGasCalendarDaysRate) +  columnDelimeter
		+ std::to_string(r.monthlyGasInjected) +  columnDelimeter
		+ std::to_string(r.monthlyGasInjectionCalendarDaysRate) +  columnDelimeter
		+ std::to_string(r.monthlyGasInjectionProdDaysRate) +  columnDelimeter
		+ std::to_string(r.monthlyGasProdDaysRate) +  columnDelimeter
		+ std::to_string(r.monthlyGasProduced) +  columnDelimeter
		+ std::to_string(r.monthlyLiquidCalendarDaysRate)+  columnDelimeter
		+ std::to_string(r.monthlyLiquidProdDaysRate) +  columnDelimeter
		+ std::to_string(r.monthlyLiquidProduced) +  columnDelimeter
		+ std::to_string(r.monthlyOilCalendarDaysRate) +  columnDelimeter
		+ std::to_string(r.monthlyOilProdDaysRate) +  columnDelimeter
		+ std::to_string(r.monthlyOilProduced) +  columnDelimeter
		+ std::to_string(r.monthlyProdBean) +  columnDelimeter
		+ std::to_string(r.monthlyProdSand) +  columnDelimeter
		+ std::to_string(r.monthlyProdTHP) +  columnDelimeter
		+ std::to_string(r.monthlyWaterCalendarDaysRate) +  columnDelimeter
		+ std::to_string(r.monthlyWaterInjected) +  columnDelimeter
		+ std::to_string(r.monthlyWaterInjectionCalendarDaysRate) +  columnDelimeter
		+ std::to_string(r.monthlyWaterInjectionProdDaysRate) +  columnDelimeter //
		+ std::to_string(r.monthlyWaterProdDaysRate) +  columnDelimeter
		+ std::to_string(r.monthlyWaterProduced) +  columnDelimeter
		+ std::to_string(r.prodDays) +  columnDelimeter
		+ std::to_string(r.prodGOR) +  columnDelimeter
		+ r.reservoir +  columnDelimeter
		+ r.tubingString +  columnDelimeter
		+ std::to_string(r.waterCut) +  columnDelimeter
        + std::to_string(r.waterGasRatio) +  columnDelimeter
		+ lastrow;

		return row;


}



tuple<vector<string>, vector<string>, vector<string>> 
AssetExplorerGeneration::GetUniqueData(vector<ProductionData>& productionDataList){
    vector<string> fieldNames;
    vector<string> resrervoirNames;
    vector<string> drainagePointNames;

    int nRows = productionDataList.size(), i = 0;
    bool check = false;
    for(i = 0; i < nRows; i++){
        
        check = IsContains(fieldNames, productionDataList[i].field);
        if(check == false){
            fieldNames.push_back(productionDataList[i].field);
        }

        check = IsContains(resrervoirNames, productionDataList[i].reservoir);
        if(check == false){
            resrervoirNames.push_back(productionDataList[i].reservoir);
        }

        check = IsContains(resrervoirNames, productionDataList[i].drainagePoint);
        if(check == false){
            drainagePointNames.push_back(productionDataList[i].drainagePoint);
        }
    }

    tuple<vector<string>, vector<string>, vector<string>> result = 
    make_tuple(fieldNames, resrervoirNames, drainagePointNames);
    
    return result;

}

vector<FieldProductionData> AssetExplorerGeneration::CreateAssetsExplorer(vector<ProductionData>& productionDataList){
    

    tuple<vector<string>, vector<string>, vector<string>> AssetNames = 
    GetUniqueData(productionDataList);

    vector<string> fieldNames = get<0>(AssetNames);
    vector<string> resrervoirNames = get<1>(AssetNames);
    vector<string> drainagePointNames = get<2>(AssetNames);

    int i, j, k,l, nFields = fieldNames.size();
    int nReservoirs = resrervoirNames.size();
    int nDrainagePoints = drainagePointNames.size();
    int nProductionDataList = productionDataList.size();
    vector<FieldProductionData> fields;

    for(k = 0; k < nFields; k++){
        vector<ReservoirProductionData> reservoirs;
        for(j = 0; j < nReservoirs; j++){
            vector<DrainagePointProductionData> draiangePoints;
            for(i = 0; i < nDrainagePoints; i++){
                vector<ProductionData> prodDataList;
                for(l = 0; l < nProductionDataList; l++){
                    if(fieldNames[k] == productionDataList[l].field
                    && resrervoirNames[j] == productionDataList[l].reservoir
                    && drainagePointNames[i] == productionDataList[l].drainagePoint){
                        prodDataList.push_back(productionDataList[j]);
                    }
                }
                int nRows = prodDataList.size();
                if(nRows > 0){
                    string table = "";
                    for(l = 0; l < nRows; l++){
                        bool isLastRow = false;
                        if(l == nRows - 1)
                        {
                            isLastRow = true;
                        }

			            table = table + GetRow(prodDataList[l], isLastRow);
                    }

                    DrainagePointProductionData drainagePointProductionData;
                    drainagePointProductionData.label = drainagePointNames[i];
                    drainagePointProductionData.icon = "";
                    drainagePointProductionData.productionDataList = table;
                    draiangePoints.push_back(drainagePointProductionData);
                }
            }

            int nRows2 = draiangePoints.size();
            if(nRows2 > 0){
                ReservoirProductionData reservoirProductionData;
                    reservoirProductionData.label = resrervoirNames[j];
                    reservoirProductionData.icon = "";
                    reservoirProductionData.children 
                    = vector<DrainagePointProductionData>(draiangePoints);
                    reservoirs.push_back(reservoirProductionData);
            }
        }

        int nRows3 = reservoirs.size();
        if(nRows3 > 0){
            FieldProductionData fieldProductionData;
                fieldProductionData.label = fieldNames[k];
                fieldProductionData.icon = "";
                for(j = 0; j < nRows3; j++){
                    std::cout << "Reservoir Name: " << reservoirs[j].label << std::endl; 
                    fieldProductionData.children.push_back(reservoirs[j]);
                }
                /* fieldProductionData.children 
                = vector<ReservoirProductionData>(reservoirs); */
                fields.push_back(fieldProductionData);
        }
    }

    return fields;
}