import { UsersClient } from "../proto/users_grpc_pb";
import { credentials } from "grpc";

const port = 3000;

export const client = new UsersClient(
  `192.168.0.14:${port}`,
  credentials.createInsecure()
);

export const noop = () => {};