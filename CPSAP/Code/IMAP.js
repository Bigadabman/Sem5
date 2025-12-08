    const Imap = require('node-imap');

    const imap = new Imap({
      user: 'keomailer6@gmail.com',
      password: 'wxtb qkth okan kpsb',
      host: 'imap.gmail.com',
      port: 993,
      tls: true,
    });

    imap.once('ready', () => {
      imap.openBox('INBOX', false, (err, box) => {
        if (err) throw err;
        imap.search(['UNSEEN', ['SINCE', new Date()]], (err, uids) => {
          if (err) throw err;
          if (!uids.length) {
            console.log('No new unread messages.');
            imap.end();
            return;
          }
          const f = imap.fetch(uids, { bodies: '', struct: true });
          f.on('message', (msg, seqno) => {
            console.log('Message #%d', seqno);
           msg.on('body', (stream, info) => {
                let buffer = '';
                stream.on('data', chunk => {
                    buffer += chunk.toString('utf8');
                });
                stream.once('end', () => {
                    const header = Imap.parseHeader(buffer);
                    console.log('HEADER:', header);

                    const body = buffer.split('\r\n\r\n')[1]; 
                    console.log('BODY:', body);
                });
                });

          });
          f.once('error', err => {
            console.log('Fetch error: ' + err);
          });
          f.once('end', () => {
            console.log('Done fetching all messages!');
            imap.end();
          });
        });
      });
    });

    imap.once('error', err => {
      console.log(err);
    });

    imap.once('end', () => {
      console.log('Connection ended');
    });

    imap.connect();