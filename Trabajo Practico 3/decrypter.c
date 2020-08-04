#include <linux/init.h>            
#include <linux/module.h>          
#include <linux/device.h>          
#include <linux/kernel.h>         
#include <linux/fs.h>             
#include <asm/uaccess.h>   

#define  DEVICE_NAME "decrypter"    
#define  CLASS_NAME  "decrypter"        

MODULE_LICENSE("GPL");            
MODULE_AUTHOR("Aichino - Altamirano ");    

static int    major;                    // El número de dispositivo mayor
static char   *message;                 // Memoria para la cadena que se pasa desde el espacio de usuario

static struct class*  d_class  = NULL; // Puntero de estructura de clase de controlador de dispositivo
static struct device* d_device = NULL; // Puntero de estructura del dispositivo del controlador del dispositivo


static int     dev_open(struct inode *, struct file *);
static int     dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

//SEEK

static struct file_operations fops =
{
   .open = dev_open,
   .read = dev_read,
   .write = dev_write,
   .release = dev_release,
};

static int __init decrypter_init(void){

   printk(KERN_INFO "Inicializando decrypter \n");

   major = register_chrdev(0, DEVICE_NAME, &fops);

   if ( major < 0 ){
      printk(KERN_ALERT "decrypter: major no se pudo registrar\n");
      return major;
   }
   printk(KERN_INFO "decrypter registrado correctamente");

   d_class = class_create(THIS_MODULE, CLASS_NAME);
 
   if ( IS_ERR(d_class) ){          
      unregister_chrdev(major, DEVICE_NAME);
      printk(KERN_ALERT "Error al registrar la clase de dispositivo\n");
      return PTR_ERR(d_class);          
   }
   printk(KERN_INFO "Clase de dispositivo creada correctamente \n");

   d_device = device_create(d_class, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);

   if ( IS_ERR(d_device) ){               
      class_destroy(d_class);           
      unregister_chrdev(major, DEVICE_NAME);
      printk(KERN_ALERT "No se pudo crear el dispositivo\n");
      return PTR_ERR(d_device);
   }

   printk(KERN_INFO "Dispositivo creado correctamente\n"); 
   return 0;
}


static void __exit decrypter_exit(void){
    
   device_destroy(d_class, MKDEV(major, 0));               // elimina el dispositivo
   class_unregister(d_class);                                    // anula el registro de la clase de dispositivo
   class_destroy(d_class);                                       // elimina la clase de dispositivo
   unregister_chrdev(major, DEVICE_NAME);                         // anula el registro del numero principal
   printk(KERN_INFO "El modulo decrypter se esta por cerrar\n");
}


static int dev_open(struct inode *inodep, struct file *filep){
   printk(KERN_INFO "Se ha abierto el dispositivo  \n");
   return 0;
}


static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
   int error_count = 0;
   
   error_count = raw_copy_to_user(buffer, message, strlen(message));

   if (error_count == 0 ){            
      printk(KERN_INFO "decrypter ha enviado %ld caracteres al usuario\n",strlen(message) );
      return 0;  
   }
   else {
      printk(KERN_ALERT  "decrypter: Error al enviar %d caracteres al usuario\n", error_count);
      return -EFAULT;             
   }
}


static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
  
  // sprintf(message, "%s(%zu letras)", buffer, len);                  
   printk(KERN_INFO "decrypter ha recibido %zu caracteres del usuario\n", len);
   return len;
}


static int dev_release(struct inode *inodep, struct file *filep){
   printk(KERN_INFO "El dispositivo se ha cerrado\n");
   return 0;
}

module_init(decrypter_init);
module_exit(decrypter_exit);