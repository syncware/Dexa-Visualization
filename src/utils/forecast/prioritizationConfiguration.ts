import { ProductionPrioritizationModel } from '../../models/wellPrioritization';

export const getProductionPrioritization = (
  productionPrioritizationModel: ProductionPrioritizationModel
) => {
  let productionPrioritization = [] as any[];
  if (
    productionPrioritizationModel.typeOfPrioritization == 'wellPrioritization'
  ) {
    productionPrioritization =
      productionPrioritizationModel.wellPrioritization.prioritizationTable;
  }

  return productionPrioritization;
};

export const getPrioritization = (
  productionPrioritizationModel: ProductionPrioritizationModel
) => {
  const parameterNamesWeightsList = [] as any[];
  var i = 0;
  let lent = 0;
  let typeOfStream = 'None';

  switch (productionPrioritizationModel.typeOfPrioritization) {
    case 'wellPrioritization':
      lent =
        productionPrioritizationModel.wellPrioritization
          .prioritizationLevelOptions.length;
      for (i = 0; i < lent; i++) {
        const parameterNamesWeight = {} as any;
        parameterNamesWeight.parameterName =
          productionPrioritizationModel.wellPrioritization.prioritizationLevelOptions[
            i
          ].title;
        parameterNamesWeight.parameterWeight =
          productionPrioritizationModel.wellPrioritization.prioritizationLevelOptions[
            i
          ].value;
        parameterNamesWeightsList.push(parameterNamesWeight);
      }
      break;
    case 'streamPrioritization':
      typeOfStream = productionPrioritizationModel.streamPrioritization
        .streamTypeOption.value as string;
      break;
    case 'projectPrioritization':
      for (
        i = 0;
        i < productionPrioritizationModel.projectPrioritization.length;
        i++
      ) {
        if (productionPrioritizationModel.projectPrioritization[i].rank == 1) {
          typeOfStream =
            productionPrioritizationModel.projectPrioritization[i].project;
          break;
        }
      }
      break;
    case 'resourceClassPrioritization':
      lent = productionPrioritizationModel.resourceClassPrioritization.length;
      for (i = 0; i < lent; i++) {
        const parameterNamesWeight = {} as any;
        parameterNamesWeight.parameterName =
          productionPrioritizationModel.resourceClassPrioritization[
            i
          ].resourceClass;
        parameterNamesWeight.parameterWeight = 1;
        parameterNamesWeightsList.push(parameterNamesWeight);
      }
      break;
  }

  const prioritization = {
    typeOfPrioritization: productionPrioritizationModel.typeOfPrioritization,
    methodOfPrioritization: 'sequential',
    targetFluid: 'oil',
    parameterNamesWeights: parameterNamesWeightsList,
    nParameterNamesWeights: parameterNamesWeightsList.length,
    typeOfStream,
  };

  return prioritization;
};

export const getNodalPrioritization = (
  productionPrioritizationModel: ProductionPrioritizationModel
) => {
  const nodalPrioritization = [] as any[];
  if (
    productionPrioritizationModel.typeOfPrioritization == 'nodalPrioritization'
  ) {
    for (
      let i = 0;
      i < productionPrioritizationModel.nodalPrioritization.length;
      i++
    ) {
      /* 
        To be modified when Sir Giddy standardize nodal prioritization
      */
      const _productionPrioritizationModel = {} as ProductionPrioritizationModel;
      _productionPrioritizationModel.typeOfPrioritization =
        'projectPrioritization';
      const projectOptions =
        productionPrioritizationModel.nodalPrioritization[i].projectOptions;
      const rankOptions =
        productionPrioritizationModel.nodalPrioritization[i].rankOptions;
      _productionPrioritizationModel.projectPrioritization = projectOptions.map(
        (row, j: number) => {
          return {
            sn: j + 1,
            project: row.value as string,
            rank: rankOptions[j].value as string,
          };
        }
      );

      const prioritization = getPrioritization(_productionPrioritizationModel);
      nodalPrioritization.push({
        ...prioritization,
        productionEquipment:
          productionPrioritizationModel.nodalPrioritization[i]
            .productionEquipment,
      });
    }
  }

  return nodalPrioritization;
};
