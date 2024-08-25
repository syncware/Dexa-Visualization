import { BadRequestError } from '../../errors/bad-request-error';

import {
  convertTableToDefaultUnits,
  convertTableToSpecifiedUnits,
} from '@syncware/units';

export async function Get_Units(): Promise<any[]> {
  let convertedData = {} as any[];

  try {
    const convertedData = convertTableToDefaultUnits({
      table: [],
      unitsRowIdx: 0,
      groupsRowIdx: 1,
      startsFromRow: 2,
      isConversionToDefaultUnit: true,
    });
  } catch (er) {
    throw new BadRequestError('Error in get units from unit service');
  }

  return convertedData;
}

export async function Get_GlobalVariableUnits(): Promise<any[]> {
  try {
    const convertedData = convertTableToDefaultUnits({
      table: [],
      unitsRowIdx: 0,
      groupsRowIdx: 1,
      startsFromRow: 2,
      isConversionToDefaultUnit: true,
    });
    return convertedData;
  } catch (er) {
    throw new BadRequestError(
      'Error in get global variable units from unit service'
    );
  }
}

export async function Get_VariableUnits(): Promise<any> {
  try {
    const convertedData = convertTableToDefaultUnits({
      table: [],
      unitsRowIdx: 0,
      groupsRowIdx: 1,
      startsFromRow: 2,
      isConversionToDefaultUnit: true,
    });
    return convertedData;
  } catch (er) {
    throw new BadRequestError('Error in get variable units from unit service');
  }
}

export async function Get_Entire_VariableUnits(
  variableUnits: any[]
): Promise<any> {
  try {
    const convertedData = convertTableToDefaultUnits({
      table: variableUnits,
      unitsRowIdx: 0,
      groupsRowIdx: 1,
      startsFromRow: 2,
      isConversionToDefaultUnit: true,
    });
    return convertedData;
  } catch (er) {
    throw new BadRequestError(
      'Error in get entire variable units from unit service'
    );
  }
}

export async function GetSelectedVariableUnits(
  variableUnits: any[]
): Promise<any> {
  try {
    const convertedData = convertTableToDefaultUnits({
      table: variableUnits,
      unitsRowIdx: 0,
      groupsRowIdx: 1,
      startsFromRow: 2,
      isConversionToDefaultUnit: true,
    });
    return convertedData;
  } catch (er) {
    throw new BadRequestError(
      'Error in get selected variable units from unit service'
    );
  }
}

export async function Convert_Unit(
  unitModel: any,
  errorMsg: string
): Promise<any> {
  try {
    const convertedData = convertTableToDefaultUnits({
      table: unitModel,
      unitsRowIdx: 0,
      groupsRowIdx: 1,
      startsFromRow: 2,
      isConversionToDefaultUnit: true,
    });
    return convertedData;
  } catch (er) {
    throw new BadRequestError(errorMsg);
  }
}

export async function Convert_to_Display_Unit_No_Variableunit(
  decks: any,
  errorMsg: string
): Promise<any> {
  try {
    const convertedData = convertTableToDefaultUnits({
      table: decks,
      unitsRowIdx: 0,
      groupsRowIdx: 1,
      startsFromRow: 2,
      isConversionToDefaultUnit: true,
    });

    return convertedData;
  } catch (er) {
    throw new BadRequestError(errorMsg);
  }
}

export async function Convert_to_Database_Unit_No_Variableunit(
  decks: any[],
  errorMsg: string
): Promise<any> {
  try {
    const convertedData = convertTableToDefaultUnits({
      table: decks,
      unitsRowIdx: 0,
      groupsRowIdx: 1,
      startsFromRow: 2,
      isConversionToDefaultUnit: true,
    });

    return convertedData;
  } catch (er) {
    throw new BadRequestError(errorMsg);
  }
}

export async function Convert_to_Database_Unit(
  decks: any[],
  errorMsg: string,
  compositeUnitsIndicies?: any[]
): Promise<any> {
  try {
    const convertedData = convertTableToSpecifiedUnits({
      table: decks,
      fromUnitsRowIdx: 0,
      toUnitsRowIdx: 1,
      startsFromRow: 2,
      compositeUnitsIndicies,
    });

    return convertedData;
  } catch (er) {
    throw new BadRequestError(errorMsg);
  }
}

export async function Convert_to_Display_Unit(
  decks: any[],
  variableUnits: any,
  errorMsg: string
): Promise<any> {
  try {
    const convertedData = convertTableToDefaultUnits({
      table: decks,
      unitsRowIdx: 0,
      groupsRowIdx: 1,
      startsFromRow: 2,
      isConversionToDefaultUnit: true,
    });

    return convertedData;
  } catch (er) {
    throw new BadRequestError(errorMsg);
  }
}

export async function Convert_to_Database_Unit_With_Project_Settings(
  decks: any[],
  variableUnits: any,
  errorMsg: string
): Promise<any> {
  try {
    const convertedData = convertTableToDefaultUnits({
      table: decks,
      unitsRowIdx: 0,
      groupsRowIdx: 1,
      startsFromRow: 2,
      isConversionToDefaultUnit: true,
    });
    return convertedData;
  } catch (er) {
    throw new BadRequestError(errorMsg);
  }
}

export async function Convert_to_Display_Unit_With_Project_Settings(
  decks: any[],
  variableUnits: any,
  errorMsg: string
): Promise<any> {
  try {
    const convertedData = convertTableToDefaultUnits({
      table: decks,
      unitsRowIdx: 0,
      groupsRowIdx: 1,
      startsFromRow: 2,
      isConversionToDefaultUnit: true,
    });

    return convertedData;
  } catch (er) {
    throw new BadRequestError(errorMsg);
  }
}

export async function Convert_ForecastResults_to_Display_Unit(
  forecastResults: any
): Promise<any> {
  const errorMsg = 'Error in converting forecast results to display unit';
  try {
    const convertedData = convertTableToDefaultUnits({
      table: forecastResults,
      unitsRowIdx: 0,
      groupsRowIdx: 1,
      startsFromRow: 2,
      isConversionToDefaultUnit: true,
    });

    return convertedData;
  } catch (er: any) {
    throw new BadRequestError(er);
  }
}
