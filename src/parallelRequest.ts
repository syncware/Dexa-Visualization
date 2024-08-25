import * as dotenv from 'dotenv';

dotenv.config();

export function Parallel(app: any, port: any) {
  const cluster = require('cluster');

  // Check the number of available CPU.
  const numCPUs = require('os').cpus().length;

  // For Master process
  if (cluster.isPrimary) {
    console.log(`Master ${process.pid} is running`);

    // Fork workers.
    for (let i = 0; i < numCPUs; i++) {
      cluster.fork();
    }

    // This event is firs when worker died
    cluster.on(
      'exit',
      (worker: { process: { pid: any } }, code: any, signal: any) => {
        console.log(`worker ${worker.process.pid} died`);
      }
    );
  }

  // For Worker
  else {
    // Workers can share any TCP connection
    // In this case it is an HTTP server

    app.listen(port, (err: any) => {
      err
        ? console.log('Error in server setup')
        : console.log(`Worker ${process.pid} started`);
    });
  }
}
