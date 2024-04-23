// Función para abrir el modal
function openModal() {
    document.getElementById('colorModal').style.display = 'flex';
  }

  // Función para cerrar el modal
  function closeModal() {
    document.getElementById('colorModal').style.display = 'none';
  }
  // Cerrar el modal si el usuario hace clic fuera de él
  window.onclick = function(event) {
    var modal = document.getElementById('colorModal');
    if (event.target == modal) {
      closeModal();
    }
  };