import express from 'express'
import path from 'path'
import logger from 'morgan'
import http from 'http'
import osc from 'osc'

const SERVER_PORT = '8080';
const UDP_PORT = '7777';
const P5_PORT = '12345';

class App {
    constructor(){
        this.exp = express();
        this.exp.use(logger('dev'));

        let port = parseInt(SERVER_PORT, 10);
        this.exp.set('port', port);

        this.server = http.createServer(this.exp);
        this.server.listen(port);
        this.server.on('error', this.onError.bind(this));
        this.server.on('listening', this.onListening.bind(this));

        this.udpPort = new osc.UDPPort({
            localAddress: '0.0.0.0',
            localPort: UDP_PORT,
            metadata: true
        });

        this.udpPort.open();

        this.exp.get('/light', (req, res)=>{

            if (req.query.p) {
                res.send('success');

                let param = req.query.p;

                this.udpPort.send({
                    address: '/',
                    args: [{ type: 'i', value: param-0 }]
                }, '0.0.0.0', P5_PORT);

                console.log('--send--');
                console.log('query: ' + param);
                console.log('--');
            } else {
                res.send('fail');
            }


        });

    }

    onError(error) {
        if (error.syscall !== 'listen') {
            throw error;
        }

        let bind = typeof port === 'string' ? 'Pipe ' + port : 'Port ' + port;

        switch (error.code) {
            case 'EACCESS':
                console.error(bind + ' requires elevated priviledges');
                process.exit(1);
                break;
            case 'EADDRINUSE':
                console.error(bind + ' is already in use');
                process.exit(1);
                break;
            default:
                throw error;
        }
    }

    onListening() {
        let addr = this.server.address();
        let bind = typeof addr === 'string' ? 'Pipe ' + addr : 'Port ' + addr.port;

        console.log('Listening on ' + bind);
    }
}

let app = new App();
