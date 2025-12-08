var nodemailer = require('nodemailer');
const { resolve } = require('path');
const mail = 'keomailer6@gmail.com';

const send = (message, password) =>{
return new Promise((resolve, reject) => {
        const transporter = nodemailer.createTransport({
            service: 'gmail',
            auth: {
                user: mail,
                pass: password
            },
            secure: true
        });

        const mailOptions = {
            from: mail,
            to: mail,
            subject: 'Lab 06 nodemailer module',
            text: message
        };

        transporter.sendMail(mailOptions, (err, info) => {
            if (err) {
                console.log(err);
                reject(err);
            }
            if (info) {
                console.log(info);
                resolve(info);
            }
        });
    })
}


module.exports = {send};

