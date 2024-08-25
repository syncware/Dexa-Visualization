import { Response } from 'express';
import MergeStream from 'merge-stream';
import { Stream } from 'stream';

const streamNetwork = (res: Response, network: any) => {
  const new_Nodes = network.nodes.map(
    (v: any) => `{"nodes":${JSON.stringify(v)}}\n\n`
  );
  const new_Edges = network.edges.map(
    (v: any) => `{"edges":${JSON.stringify(v)}}\n\n`
  );

  const nodesStream = Stream.Readable.from(new_Nodes);
  const edgesStream = Stream.Readable.from(new_Edges);

  const allStreams = MergeStream(edgesStream, nodesStream);
  allStreams.on('error', () => {
    res.status(401).send();
  });
  allStreams.on('end', () => {
    res.status(200).send();
  });

  allStreams.pipe(res);
};

export default streamNetwork;
