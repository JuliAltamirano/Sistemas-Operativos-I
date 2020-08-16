#include <linux/init.h>            
#include <linux/module.h>          
#include <linux/device.h>          
#include <linux/kernel.h>         
#include <linux/fs.h>             
#include <asm/uaccess.h>   

#define  DEVICE_NAME "encrypt"    
#define  CLASS_NAME  "encrypt"        

MODULE_LICENSE("GPL");            
MODULE_AUTHOR("Aichino - Altamirano");    

static int major;
static char message[5000] = {0};

static struct class*  e_class  = NULL;
static struct device* e_device = NULL;

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

//SEEK

static struct file_operations fops =
{
   .open = dev_open,
   .read = dev_read,
   .write = dev_write,
   .release = dev_release
};

static int __init encrypt_init(void){

   printk(KERN_INFO "Inicializando driver '%s'\n", DEVICE_NAME);

   major = register_chrdev(0, DEVICE_NAME, &fops);

   if ( major < 0 ){
      printk(KERN_ERR "ERROR: no se pudo registrar el driver. DRIVER: %s\n", DEVICE_NAME);
      return major;
   }
   printk(KERN_INFO "El driver '%s' ha sido registrado correctamente\n", DEVICE_NAME);

   e_class = class_create(THIS_MODULE, CLASS_NAME);
 
   if ( IS_ERR(e_class) ){
      printk(KERN_ERR "ERROR: no se pudo crear la clase del dispositivo. DRIVER: %s\n", DEVICE_NAME);
      printk(KERN_INFO "Liberando numeros de dispositivo del driver '%s'\n", DEVICE_NAME);
      unregister_chrdev(major, DEVICE_NAME);
      return PTR_ERR(e_class);
   }
   printk(KERN_INFO "La clase del dispositivo para el driver '%s' ha sido creada correctamente\n", DEVICE_NAME);

   e_device = device_create(e_class, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);

   if ( IS_ERR(e_device) ){
      printk(KERN_ERR "ERROR: No se pudo crear el dispositivo. DRIVER: %s\n", DEVICE_NAME);
      printk(KERN_INFO "Eliminando la clase del dispositivo del driver '%s'\n", DEVICE_NAME);
      class_destroy(e_class);
      printk(KERN_INFO "Liberando numeros de dispositivo del driver '%s'\n", DEVICE_NAME);
      unregister_chrdev(major, DEVICE_NAME);
      return PTR_ERR(e_device);
   }

   printk(KERN_INFO "El dispositivo del driver '%s' ha sido creado correctamente\n", DEVICE_NAME); 
   return 0;
}

static void __exit encrypt_exit(void){
   
   printk(KERN_INFO "Finalizando driver '%s'\n", DEVICE_NAME);
   printk(KERN_INFO "Eliminando el dispositivo del driver '%s'\n", DEVICE_NAME);
   device_destroy(e_class, MKDEV(major, 0));
   printk(KERN_INFO "Liberando el registro y eliminando la clase del dispositivo del driver '%s'\n", DEVICE_NAME);
   class_unregister(e_class);
   class_destroy(e_class);
   printk(KERN_INFO "Liberando numeros de dispositivo del driver '%s'\n", DEVICE_NAME);
   unregister_chrdev(major, DEVICE_NAME);
}

static int dev_open(struct inode *inodep, struct file *filep){

   printk(KERN_INFO "Abriendo el archivo del dispositivo. DRIVER: %s\n", DEVICE_NAME);
   return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
   
   int bytes_not_copied;
   
   printk(KERN_INFO "Leyendo el archivo del dispositivo. DRIVER: %s\n", DEVICE_NAME);
   bytes_not_copied = raw_copy_to_user(buffer, message, strlen(message));

   if (bytes_not_copied == 0 ){            
      printk(KERN_INFO "El driver '%s' ha copiado %ld caracteres al usuario\n", DEVICE_NAME, strlen(message));
      return 0;  
   }
   else {
      printk(KERN_ERR "ERROR: no se pudo copiar los caracteres al usuario. DRIVER: %s\n", DEVICE_NAME);
      return -EFAULT;             
   }
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
  
   printk(KERN_INFO "Escribiendo el archivo del dispositivo. DRIVER: %s\n", DEVICE_NAME);
   sprintf(message, "%s", buffer);
   printk(KERN_INFO "El driver '%s' ha recibido del usuario %ld caracteres y procede a escribirlos en el archivo del dispositivo\n", DEVICE_NAME, len);
   return len;
}

static int dev_release(struct inode *inodep, struct file *filep){

   printk(KERN_INFO "Cerrando el archivo del dispositivo. DRIVER: %s\n", DEVICE_NAME);
   return 0;
}

module_init(encrypt_init);
module_exit(encrypt_exit);