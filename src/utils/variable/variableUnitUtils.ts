// export function GetFacilitiesInputHeaders(): Object[] {
//   let data: any = {
//     primary: "Primary",
//     secondary: "Secondary",
//     liquidCapacity1P: "Liquid Capacity [1P]",
//     gasCapacity1P: "Gas Capacity [1P]",
//     scheduledDeferment1P: "Scheduled Deferment [1P]",
//     unscheduledDeferment1P: "UnScheduled Deferment [1P]",
//     thirdPartyDeferment1P: "ThirdParty Deferment [1P]",
//     crudeOilLosses1P: "CrudeOil Losses [1P]",
//     ownUseGas1P: "Gas Own Use [1P]",
//     gasDemand1P: "Gas Demand [1P]",
//     fDate1P: "Forecast Date [1P]",
//     liquidCapacity2P: "Liquid Capacity [2P]",
//     gasCapacity2P: "Gas Capacity [2P]",
//     scheduledDeferment2P: "Scheduled Deferment [2P]",
//     unscheduledDeferment2P: "UnScheduled Deferment [2P]",
//     thirdPartyDeferment2P: "ThirdParty Deferment [2P]",
//     crudeOilLosses2P: "CrudeOil Losses [2P]",
//     ownUseGas2P: "Gas Own Use [2P]",
//     gasDemand2P: "Gas Demand [2P]",
//     fDate2P: "Forecast Date [2P]",
//     liquidCapacity3P: "Liquid Capacity [3P]",
//     gasCapacity3P: "Gas Capacity [3P]",
//     scheduledDeferment3P: "Scheduled Deferment [3P]",
//     unscheduledDeferment3P: "UnScheduled Deferment [3P]",
//     thirdPartyDeferment3P: "ThirdParty Deferment [3P]",
//     crudeOilLosses3P: "CrudeOil Losses [3P]",
//     ownUseGas3P: "Gas Own Use [3P]",
//     gasDemand3P: "Gas Demand [3P]",
//     fDate3P: "Forecast Date [3P]",
//     none: "None",
//   };

export function GetFacilitiesInputHeaders(): Object[] {
  let data: any = {
    sn: 'SN',
    node1: 'Node1',
    node2: 'Node2',
    node3: 'Node3',
    node4: 'Node4',
    node5: 'Node5',
    node6: 'Node6',
    node7: 'Node7',
    node8: 'Node8',
    node9: 'Node9',
    node10: 'Node10',
    node11: 'Node11',
    node12: 'Node12',
    node13: 'Node13',
    node14: 'Node14',
    node15: 'Node15',
    node16: 'Node16',
    node17: 'Node17',
    node18: 'Node18',
    node19: 'Node19',
    node20: 'Node20',
    none: 'None',
  };

  const results = Object.keys(data).map((k) => ({
    variableName: k,
    variableTitle: data[k],
  }));

  return results;
}

export function GetForecastInputHeaders(): Object[] {
  let data: any = {
    forecastVersion: 'Forecast Version',
    asset: 'Asset',
    field: 'Field',
    reservoir: 'Reservoir',
    well: 'Well',
    drainagePoint: 'Drainage Point',
    string: 'String',
    module: 'Module',
    projectCode: 'Project Code',
    projectName: 'Project Name',
    facilities: 'Facilities',
    hydrocarbonStream: 'Hydrocarbon Stream',
    hydrocarbonType: 'Hydrocarbon Type',
    terminal: 'Terminal',
    resourceClass: 'Resource Class',
    oilUR1P1C: 'Oil UR [1P1C]',
    oilUR2P2C: 'Oil UR [2P2C]',
    oilUR3P3C: 'Oil UR [3P3C]',
    Np: 'Np',
    gasUR1P1C: 'Gas UR [1P1C]',
    gasUR2P2C: 'Gas UR [2P2C]',
    gasUR3P3C: 'Gas UR [3P3C]',
    Gp: 'Gp',
    initOilGasRate1P1C: 'Init. Oil/Gas Rate [1P1C]',
    initOilGasRate2P2C: 'Init. Oil/Gas Rate [2P2C]',
    initOilGasRate3P3C: 'Init. Oil/Gas Rate [3P3C]',
    abandOilGasRate1P1C: 'Aband. Oil/Gas Rate [1P1C]',
    abandOilGasRate2P2C: 'Aband. Oil/Gas Rate [2P2C]',
    abandOilGasRate3P3C: 'Aband. Oil/Gas Rate [3P3C]',
    initBSWWGR: 'Init. BSW/WGR',
    abandBSWWGR1P1C: 'Aband. BSW/WGR [1P1C]',
    abandBSWWGR2P2C: 'Aband. BSW/WGR [2P2C]',
    abandBSWWGR3P3C: 'Aband. BSW/WGR [3P3C]',
    initGORCGR: 'Init. GOR/CGR',
    abandGORCGR1P1C: 'Aband. GOR/CGR [1P1C]',
    abandGORCGR2P2C: 'Aband. GOR/CGR [2P2C]',
    abandGORCGR3P3C: 'Aband. GOR/CGR [3P3C]',
    plateauPeriod: 'Plateau Period',
    onStreamDate1P1C: 'On-stream Date-[1P1C]',
    onStreamDate2P2C: 'On-stream Date-[2P2C]',
    onStreamDate3P3C: 'On-stream Date-[3P3C]',
    remarks: 'Remarks',
    developmentTranche: 'Development Tranche',
    none: 'None',
  };

  const results = Object.keys(data).map((k) => ({
    variableName: k,
    variableTitle: data[k],
  }));

  return results;
}

export function GetForecastResultHeaders(): Object[] {
  let data: any = {
    day: 'Day',
    month: 'Month',
    year: 'Year',
    oilRate: 'Oil Rate',
    gasRate: 'Gas Rate',
    waterRate: 'Water Rate',
    liquidRate: 'Liquid Rate',
    gasFlare: 'Gas Flare',
    GOR: 'GOR',
    CGR: 'CGR',
    BSW: 'BSW',
    WGR: 'WGR',
    cumOilProd: 'Cumulative Oil Produced',
    cumGasProd: 'Cumulative Gas Produced',
    cumWaterProd: 'Cumulative Water Produced',
    description: 'Description',
    decisionVariable: 'Decision Variable',
    ownUseGas: 'Gas Own Use',
    gasDemand: 'Gas Demand',
    crudeOilLosses: 'Crude Oil Losses',
    moduleName: 'Module Name',
    customDate: 'Custom Date',

    hydrocarbonStream: 'Hydrocarbon Stream',
    hydrocarbonType: 'Hydrocarbon Type',
    terminal: 'Terminal',
    cutBack: 'Cut Back',
    URo: 'Ultimate Oil Recovery',
    URg: 'Ultimate Gas Recovery',
    isFlowing: 'Flowing',
    cutBackUpperBound: 'Cut Back Upper Bound',
    isPlateau: 'Plateau',
    declineRate: 'Decline Rate',

    forecastVersion: 'Forecast Version',
    asset: 'Asset',
    field: 'Field',
    reservoir: 'Reservoir',
    drainagePoint: 'Drainage Point',
    string: 'String',
    facilities: 'Facilities',
    developmentTranche: 'Development Tranche',
    forecastProfiles: 'Forecast Profiles',
  };

  const results = Object.keys(data).map((k) => ({
    variableName: k,
    variableTitle: data[k],
  }));

  return results;
}
