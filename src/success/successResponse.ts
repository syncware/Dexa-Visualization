export class SuccessResponse {
  public static Success(data: any, statusCode: number = 200): object {
    let info = {
      statusCode: statusCode,
      data: data,
      success: true,
    };

    return info;
  }

  public static Success3(
    success: boolean,
    data: any = null,
    statusCode: number = 200
  ): object {
    let info = {
      statusCode: statusCode,
      data: data,
      success: true,
    };

    return info;
  }
}
