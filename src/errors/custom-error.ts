export abstract class CustomError extends Error {
  protected constructor(message: string) {
    super(message);

    // given the base class is a built-in class
    Object.setPrototypeOf(this, CustomError.prototype);
  }

  abstract statusCode: number;

  abstract serializeErrors(): { message: string; field?: string }[];
}
