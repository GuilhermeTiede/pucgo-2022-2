import { UsersClient } from "../proto/users_grpc_pb";
import { credentials } from "grpc";

const port = 50051;

export const client = new UsersClient(
  `10.43.27.226:${port}`,
  credentials.createInsecure()
);

export const noop = () => {};