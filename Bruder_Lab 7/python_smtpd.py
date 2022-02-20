#!/usr/bin/python

import sys
# from datetime import datetime
import asyncore
from smtpd import SMTPServer
import logging

# This server logs messages, and optionally prints them on screen

class MyEmailServer(SMTPServer):

    def process_message(self, peer, mailfrom, rcpttos, data, **kwargs):
        logging.info('Received from:'+(':'.join(map(str, peer))))
        logging.info('From:' + mailfrom)
        logging.info('To:' + (','.join(rcpttos)))
        string_data = data.decode('utf-8')
        logging.info('Data:' + string_data)
        # you can turn the print() on (by -v option) to see messages on screen
        if verbose:
            print('Receiving message from:', string_peer)
            print('Message addressed from:', mailfrom)
            print('Message addressed to  :', ','.join(rcpttos))
            print(data)

        if len(rcpttos) != 1:
            err = '554 Too many recipients'
            logging.info(err)
            if verbose:
                print(err)
            return err

        if ',' in rcpttos[0]:
            err = '554 Bad recipient'
            logging.info(err)
            if verbose:
                print(err)
            return err

        if len(data) > 1024:
            err = '554 Message is too long'
            logging.info(err)
            if verbose:
                print(err)
            return err

def run():
    hostname = '127.0.0.1'
    foo = MyEmailServer((hostname, 2525), None)
    logging.basicConfig(format='%(message)s', 
            filename='smtpd_python.log', 
            level=logging.INFO)
    logging.info('Python smtpd started on %s.' % hostname)
    try:
        asyncore.loop()
    except KeyboardInterrupt:
        pass


if __name__ == '__main__':
    verbose = 0
    if len(sys.argv) > 1 and sys.argv[1] == '-v' :
        verbose = 1
    run()

