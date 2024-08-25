const SplitFlowstationsGasFacilities = (forecastDataByStation: any) => {
  const flowStationsData: any = {};
  const gasFacilitiesData: any = {};

  for (const key in forecastDataByStation) {
    const data = forecastDataByStation[key][0];
    const hydrocarbonStream = data["hydrocarbonStream"].toLowerCase().trim();

    if (hydrocarbonStream === "gas")
      gasFacilitiesData[key] = forecastDataByStation[key];
    else if (hydrocarbonStream === "oil")
      flowStationsData[key] = forecastDataByStation[key];
  }

  return { flowStationsData, gasFacilitiesData };
};

export default SplitFlowstationsGasFacilities;
